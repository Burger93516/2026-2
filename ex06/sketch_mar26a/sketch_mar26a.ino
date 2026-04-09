   // ex06 警车双闪（双通道反相PWM）
const int LED_A = 4;   // 第一个LED
const int LED_B = 17;  // 第二个LED

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  // A从0→255，B从255→0
  for (int i = 0; i <= 255; i++) {
    analogWrite(LED_A, i);
    analogWrite(LED_B, 255 - i);
    delay(5);
  }
  // A从255→0，B从0→255
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED_A, i);
    analogWrite(LED_B, 255 - i);
    delay(5);
  }
}