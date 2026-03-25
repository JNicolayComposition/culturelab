const int touchPin1 = 27;
const int touchPin2 = 33;
const int touchPin3 = 32;

int threshold1 = 60;
int threshold2 = 60;
int threshold3 = 60;

bool wasTouched1 = false;
bool wasTouched2 = false;
bool wasTouched3 = false;

unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch-Test mit 3 Pins");
}

void loop() {
  int value1 = touchRead(touchPin1);
  int value2 = touchRead(touchPin2);
  int value3 = touchRead(touchPin3);

  bool isTouched1 = (value1 < threshold1);
  bool isTouched2 = (value2 < threshold2);
  bool isTouched3 = (value3 < threshold3);

  if (isTouched1 && !wasTouched1) {
    Serial.print("TOUCH: Pin 27 | Wert: ");
    Serial.println(value1);
  }
  if (!isTouched1 && wasTouched1) {
    Serial.println("LOS: Pin 27");
  }

  if (isTouched2 && !wasTouched2) {
    Serial.print("TOUCH: Pin 33 | Wert: ");
    Serial.println(value2);
  }
  if (!isTouched2 && wasTouched2) {
    Serial.println("LOS: Pin 33");
  }

  if (isTouched3 && !wasTouched3) {
    Serial.print("TOUCH: Pin 32 | Wert: ");
    Serial.println(value3);
  }
  if (!isTouched3 && wasTouched3) {
    Serial.println("LOS: Pin 32");
  }

  if (millis() - lastPrint >= 500) {
    Serial.print("Rohwerte | 27: ");
    Serial.print(value1);
    Serial.print(" | 33: ");
    Serial.print(value2);
    Serial.print(" | 32: ")