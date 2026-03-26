const int ledPin = 12;

// SOS节奏：亮/灭交替时间（单位：ms）
unsigned int pattern[] = {
  // S: ···
  200, 200, 200, 200, 200, 600,
  // O: ---
  600, 200, 600, 200, 600, 600,
  // S: ···
  200, 200, 200, 200, 200, 2000
};

const int patternLength = sizeof(pattern) / sizeof(pattern[0]);

int stepIndex = 0;          // 当前步骤
bool ledState = HIGH;      // 当前LED状态（从亮开始）

unsigned long previousMillis = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // 到时间切换状态
  if (currentMillis - previousMillis >= pattern[stepIndex]) {
    previousMillis = currentMillis;

    // 切换LED状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    // 进入下一步
    stepIndex++;

    // 循环播放SOS
    if (stepIndex >= patternLength) {
      stepIndex = 0;
    }
  }
}