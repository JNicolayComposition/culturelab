#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Touch-Pins
const int touchPin1 = 27;
const int touchPin2 = 33;
const int touchPin3 = 32;

// Thresholds
int threshold1 = 60;
int threshold2 = 60;
int threshold3 = 60;

// Touch-Zustände
bool wasTouched1 = false;
bool wasTouched2 = false;
bool wasTouched3 = false;

// BLE
BLECharacteristic *pCharacteristic;
BLEServer *pServer;
BLEAdvertising *pAdvertising;
bool deviceConnected = false;

// UUIDs
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-1234-1234-abcdefabcdef"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* server) override {
    deviceConnected = true;
    Serial.println("BLE verbunden");
  }

  void onDisconnect(BLEServer* server) override {
    deviceConnected = false;
    Serial.println("BLE getrennt");

    delay(200);
    pAdvertising->start();
    Serial.println("Advertising neu gestartet");
  }
};

void sendTrigger(const char* message) {
  if (deviceConnected) {
    pCharacteristic->setValue(message);
    pCharacteristic->notify();

    Serial.print("Gesendet: ");
    Serial.println(message);
  } else {
    Serial.print("Nicht gesendet, kein Geraet verbunden: ");
    Serial.println(message);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 BLE Touch Trigger startet...");

  BLEDevice::init("ESP32-Touch-Trigger");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setValue("ready");

  pService->start();

  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->start();

  Serial.println("BLE Advertising gestartet");
}

void loop() {
  int value1 = touchRead(touchPin1);
  int value2 = touchRead(touchPin2);
  int value3 = touchRead(touchPin3);

  bool isTouched1 = (value1 < threshold1);
  bool isTouched2 = (value2 < threshold2);
  bool isTouched3 = (value3 < threshold3);

  if (isTouched1 && !wasTouched1) {
    Serial.print("TOUCH 27 | Wert: ");
    Serial.println(value1);
    sendTrigger("sound1_on");
  }
  if (!isTouched1 && wasTouched1) {
    Serial.println("LOS 27");
    sendTrigger("sound1_off");
  }

  if (isTouched2 && !wasTouched2) {
    Serial.print("TOUCH 33 | Wert: ");
    Serial.println(value2);
    sendTrigger("sound2_on");
  }
  if (!isTouched2 && wasTouched2) {
    Serial.println("LOS 33");
    sendTrigger("sound2_off");
  }

  if (isTouched3 && !wasTouched3) {
    Serial.print("TOUCH 32 | Wert: ");
    Serial.println(value3);
    sendTrigger("sound3_on");
  }
  if (!isTouched3 && wasTouched3) {
    Serial.println("LOS 32");
    sendTrigger("sound3_off");
  }

  wasTouched1 = isTouched1;
  wasTouched2 = isTouched2;
  wasTouched3 = isTouched3;

  delay(30);
}
