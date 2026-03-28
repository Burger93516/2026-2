// ex04 触摸自锁开关
const int TOUCH_PIN = 2;  // 触摸传感器引脚
const int LED_PIN   = 9;  // LED引脚

bool ledState = false;          // LED当前状态
bool lastTouchState = false;    // 上一次触摸状态
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 防抖50ms

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  // 读取当前触摸值
  int currentTouch = digitalRead(TOUCH_PIN);
  unsigned long now = millis();

  // 防抖过滤
  if (currentTouch != lastTouchState) {
    lastDebounceTime = now;
  }

  // 防抖时间满足 + 检测到**按下瞬间**（边缘检测）
  if ((now - lastDebounceTime) > debounceDelay) {
    // 上一次没按，现在按了 → 翻转LED
    if (currentTouch == HIGH && lastTouchState == LOW) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
    lastTouchState = currentTouch;
  }
}