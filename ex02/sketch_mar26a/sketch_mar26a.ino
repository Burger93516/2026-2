const int ledPin = 12;

unsigned long previousMillis = 0;
const long interval = 500;  // 500ms 翻转一次 → 1Hz

bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // 翻转LED状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}