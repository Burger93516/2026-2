#include <WiFi.h>
#include <WebServer.h>

// WiFi 信息
const char* ssid = "张小倍QAQ";
const char* password = "iu5201314";

// LED 引脚
const int LED_PIN = 2;

// 网页服务器
WebServer server(80);

// 主页：显示调光界面
void handleHome() {
  String html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>LED调光</title>
</head>
<body>
  <h2>ESP32 无极调光</h2>
  <p>亮度：<span id="val">0</span></p>
  <input type="range" min="0" max="255" oninput="update(this.value)">
  
  <script>
    function update(v) {
      document.getElementById("val").innerText = v;
      fetch("/set?b="+v);
    }
  </script>
</body>
</html>
)HTML";
  server.send(200, "text/html", html);
}

// 处理调光指令
void handleSet() {
  int bright = server.arg("b").toInt();
  analogWrite(LED_PIN, bright);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // 连接 WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi OK");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // 设置网址
  server.on("/", handleHome);
  server.on("/set", handleSet);
  
  server.begin();
}

void loop() {
  server.handleClient();
}