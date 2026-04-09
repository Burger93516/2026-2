#include <Arduino.h>

// 引脚定义
#define TOUCH_PIN  T0   // 触摸引脚
#define LED_PIN    21   // LED引脚
#define THRESHOLD  200  // 触摸阈值

// 呼吸灯参数
int dutyCycle = 0;
bool isIncreasing = true;

// 触摸防抖
bool isTouched = false;
unsigned long lastTouchTime = 0;
const unsigned long debounceDelay = 50;

// 档位控制：慢、中、快
int currentSpeed = 1;
const int stepSlow = 1;
const int stepMid  = 5;
const int stepFast = 10;
int currentStep = stepSlow;

// 触摸中断
void gotTouch() {
  unsigned long now = millis();
  if (now - lastTouchTime < debounceDelay) return;
  lastTouchTime = now;

  int val = touchRead(TOUCH_PIN);
  if (val < THRESHOLD && !isTouched) {
    // 切换档位
    currentSpeed = (currentSpeed % 3) + 1;
    switch(currentSpeed) {
      case 1: currentStep = stepSlow; break;
      case 2: currentStep = stepMid;  break;
      case 3: currentStep = stepFast; break;
    }
    isTouched = true;
    Serial.print("档位：");
    Serial.println(currentSpeed);
  } else if (val >= THRESHOLD && isTouched) {
    isTouched = false;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // 老版本ESP32兼容写法
  ledcAttach(LED_PIN, 5000, 8);
  
  // 触摸中断
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  // 呼吸灯
  if (isIncreasing) {
    dutyCycle += currentStep;
    if (dutyCycle >= 255) {
      dutyCycle = 255;
      isIncreasing = false;
    }
  } else {
    dutyCycle -= currentStep;
    if (dutyCycle <= 0) {
      dutyCycle = 0;
      isIncreasing = true;
    }
  }

  ledcWrite(LED_PIN, dutyCycle);
  delay(10);
}