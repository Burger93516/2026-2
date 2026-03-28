// ex05 多档位触摸调速呼吸灯
const int TOUCH_PIN = 2;
const int LED_PIN   = 9;

bool lastTouch = false;
int speedLevel = 1;       // 1=慢 2=中 3=快
int step = 5;              // 亮度变化步长

// 防抖变量
unsigned long lastDebounce = 0;
const int DEBOUNCE = 50;

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // ===================== 触摸切换档位 =====================
  int nowTouch = digitalRead(TOUCH_PIN);
  unsigned long now = millis();

  if (nowTouch != lastTouch && (now - lastDebounce) > DEBOUNCE) {
    if (nowTouch == HIGH) {
      speedLevel++;          // 档位+1
      if (speedLevel > 3) { // 循环 1→2→3→1
        speedLevel = 1;
      }
      // 根据档位调整呼吸速度（步长越大越快）
      if (speedLevel == 1) step = 3;   // 慢
      if (speedLevel == 2) step = 8;   // 中
      if (speedLevel == 3) step = 15;  // 快
    }
    lastTouch = nowTouch;
    lastDebounce = now;
  }

  // ===================== 呼吸灯逻辑 =====================
  static int brightness = 0;
  static int fadeDir = 1;

  analogWrite(LED_PIN, brightness);
  brightness += fadeDir * step;

  // 反转方向
  if (brightness <= 0 || brightness >= 255) {
    fadeDir = -fadeDir;
  }
  delay(15);
}