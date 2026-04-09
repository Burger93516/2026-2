#include <Arduino.h>

// 引脚定义
<<<<<<< HEAD
#define TOUCH_PIN  T0   // 触摸引脚
#define LED_PIN    21   // LED引脚
#define THRESHOLD  200  // 触摸阈值

// 呼吸灯参数
int dutyCycle = 0;
bool isIncreasing = true;

// 触摸防抖
=======
#define TOUCH_PIN  32   // 触摸引脚
#define LED_PIN    2     // LED引脚
#define THRESHOLD  600    // 触摸阈值

// 呼吸灯参数
const int freq = 5000;
const int resolution = 8;
int dutyCycle = 0;
bool isIncreasing = true;

// 触摸自锁与防抖
bool ledState = false;
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
bool isTouched = false;
unsigned long lastTouchTime = 0;
const unsigned long debounceDelay = 50;

<<<<<<< HEAD
// 档位控制：慢、中、快
int currentSpeed = 1;
const int stepSlow = 1;
const int stepMid  = 5;
const int stepFast = 10;
int currentStep = stepSlow;

// 触摸中断
=======
// 档位控制：1=慢，2=中，3=快
int currentSpeed = 1;
const int stepSlow = 1;    // 慢档步长
const int stepMid  = 5;   // 中档步长
const int stepFast = 10;  // 快档步长
int currentStep = stepSlow;

// 触摸中断函数（带防抖）
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
void gotTouch() {
  unsigned long now = millis();
  if (now - lastTouchTime < debounceDelay) return;
  lastTouchTime = now;

  int val = touchRead(TOUCH_PIN);
  if (val < THRESHOLD && !isTouched) {
<<<<<<< HEAD
    // 切换档位
=======
    // 触摸瞬间：切换档位
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
    currentSpeed = (currentSpeed % 3) + 1;
    switch(currentSpeed) {
      case 1: currentStep = stepSlow; break;
      case 2: currentStep = stepMid;  break;
      case 3: currentStep = stepFast; break;
    }
    isTouched = true;
<<<<<<< HEAD
    Serial.print("档位：");
=======
    Serial.print("当前档位: ");
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
    Serial.println(currentSpeed);
  } else if (val >= THRESHOLD && isTouched) {
    isTouched = false;
  }
}

void setup() {
  Serial.begin(115200);
<<<<<<< HEAD
  pinMode(LED_PIN, OUTPUT);
  
  // 老版本ESP32兼容写法
  ledcAttach(LED_PIN, 5000, 8);
  
  // 触摸中断
=======
  // 初始化PWM
  ledcAttach(LED_PIN, freq, resolution);
  // 初始化触摸中断
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
<<<<<<< HEAD
  // 呼吸灯
=======
  // 呼吸灯核心逻辑
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
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
<<<<<<< HEAD

  ledcWrite(LED_PIN, dutyCycle);
  delay(10);
=======
  ledcWrite(LED_PIN, dutyCycle);
  delay(10);  // 基础延时，步长决定呼吸快慢
>>>>>>> 1a534836466a89f576a342df067d170f2915191d
}