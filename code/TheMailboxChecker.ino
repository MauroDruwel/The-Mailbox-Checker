#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

const char* serverName = "YourDiscordWebhookURL";
void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  int i = 0;
  while(WiFi.status() != WL_CONNECTED && i<10) {
    delay(500);
    Serial.print(".");
  }
  if(i>= 10){
    Serial.println("Starting DeepSleep...");
    digitalWrite(12,LOW);
    esp_deep_sleep_start();
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  delay(1000);
  Serial.println(WiFi.localIP());
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"content\":\"Brievenbus open!\"}");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }
  digitalWrite(12,LOW);
  delay(1000);
  esp_deep_sleep_start();
}

void loop() {
}