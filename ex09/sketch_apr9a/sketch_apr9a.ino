#include <WiFi.h>
#include <WebServer.h>

// WiFi 信息
const char* ssid = "张小倍QAQ";
const char* password = "iu5201314";

#define TOUCH_PIN T0  // 触摸引脚
WebServer server(80);

// 主页（极简网页）
void handleRoot() {
  String html = "<html><head><meta charset=utf-8></head><body style='text-align:center'>";
  html += "<h1>触摸传感器数值</h1>";
  html += "<div id='val' style='font-size:60px'>--</div>";
  html += "<script>setInterval(()=>{fetch('/data').then(r=>r.text()).then(v=>document.getElementById('val').innerText=v)},100)</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// 返回触摸数据
void handleData() {
  int value = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(value));
}

void setup() {
  Serial.begin(115200);
  
  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi OK");
  Serial.println("IP: " + WiFi.localIP().toString());

  // 路由
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}