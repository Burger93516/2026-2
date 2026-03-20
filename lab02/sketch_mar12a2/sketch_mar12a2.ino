// 定义板载LED引脚，避免使用"魔法数字"
#define LED_PIN_Y 12
void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  // 初始化板载LED引脚为输出模式
  pinMode(LED_PIN_Y, OUTPUT);  
}

void loop() {
  Serial.println("Hello ESP32!");
  // SOS 示例思路
// S: 短闪3次
for(int i=0; i<3; i++) 
{ digitalWrite(LED_PIN_Y, HIGH); delay(200); digitalWrite(LED_PIN_Y, LOW); delay(200); }
delay(500); // 字母间隔
// O: 长闪3次
for(int i=0; i<3; i++) 
{ digitalWrite(LED_PIN_Y, HIGH); delay(600); digitalWrite(LED_PIN_Y, LOW); delay(200); }
delay(500);
// S: 短闪3次
for(int i=0; i<3; i++)
 { digitalWrite(LED_PIN_Y, HIGH); delay(200); digitalWrite(LED_PIN_Y, LOW); delay(200); }
delay(2000); // 单词间隔
}