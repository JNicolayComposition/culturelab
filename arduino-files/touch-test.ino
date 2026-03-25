// Schritt 1: Touch-Pin am ESP32 testen
// Board: ESP32 Dev Module
// Test-Pin: GPIO 27 (Touch-Pin)

const int touchPin = 27;

// Schwellenwert: muss oft etwas angepasst werden
// Beim ESP32 sinkt der Messwert bei Berührung.
int threshold = 25;

bool wasTouched = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 Touch-Test startet...");
  Serial.println("Beruehre GPIO 27 / Touch-Pin");
}

void loop() {
  int value = touchRead(touchPin);

  Serial.print("Touch-Wert: ");
  Serial.println(value);

  bool isTouched = (value < threshold);

  if (isTouched && !wasTouched) {
    Serial.println(">>> TOUCH erkannt");
  }

  if (!isTouched && wasTouched) {
    Serial.println(">>> losgelassen");
  }

  wasTouched = isTouched;

  delay(100);
}