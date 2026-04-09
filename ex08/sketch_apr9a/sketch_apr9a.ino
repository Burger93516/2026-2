#include <WiFi.h>
#include <WebServer.h>

// WiFi 信息（你自己的）
const char* ssid = "张小倍QAQ";
const char* password = "iu5201314";

#define TOUCH_GATE 600  // 触摸阈值
const int LED_PIN = 2;
const int TOUCH_PIN = 13;  // 触摸引脚

WebServer server(80);

bool isArmed = false;
bool isAlarming = false;

// 主页
void homePage() {
  String arm = isArmed ? "已布防" : "未布防";
  String alarm = isAlarming ? "报警中！" : "正常";

  String html = "<html><head><meta charset='UTF-8'></head><body style='text-align:center'>";
  html += "<h2>ESP32 安防报警</h2>";
  html += "<p>系统：" + arm + "</p>";
  html += "<p>报警：" + alarm + "</p>";
  html += "<p><a href='/arm'><button>布防</button></a></p>";
  html += "<p><a href='/disarm'><button>撤防</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// 布防
void arm() {
  isArmed = true;
  isAlarming = false;
  server.sendHeader("Location","/");
  server.send(303);
}

// 撤防
void disarm() {
  isArmed = false;
  isAlarming = false;
  server.sendHeader("Location","/");
  server.send(303);
}

// ====== 新增：WiFi 连接函数 ======
void connectWiFi() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("正在连接 WiFi: ");
  Serial.println(ssid);
  
  // 等待连接
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // 连接成功
  Serial.println("");
  Serial.println("WiFi 连接成功！");
  Serial.print("IP 地址：");
  Serial.println(WiFi.localIP()); // 这里会打印出你要访问的网址
}

void setup() {
  connectWiFi(); // 先连上网
  pinMode(LED_PIN, OUTPUT);

  // 网页路由
  server.on("/", homePage);
  server.on("/arm", arm);
  server.on("/disarm", disarm);

  // 启动服务器
  server.begin();
  Serial.println("Web 服务器已启动");
}

void loop() {
  server.handleClient();

  // 读取触摸传感器
  int touchVal = touchRead(TOUCH_PIN);
  Serial.println(touchVal); // 可查看触摸值，方便调试

  // 布防状态下检测触摸
  if (isArmed && !isAlarming) {
    if (touchVal < TOUCH_GATE) {  // 触摸触发
      isAlarming = true;
    }
  }

  // 报警闪烁
  if (isAlarming) {
    digitalWrite(LED_PIN, millis() % 200 < 100);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}