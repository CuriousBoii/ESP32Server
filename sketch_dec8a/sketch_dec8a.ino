#include <HTTPClient.h>;
#include <WiFi.h>;
#include <ArduinoJson.h>;

const char* ssid = "Redmi";
const char* password = "9900092148";
int n = 0;
void setup(){
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    
}

void loop(){
  HTTPClient client;
  client.begin("https://jsonplaceholder.typicode.com/posts/1/comments?id="+String(n+1));
  int httpscode = client.GET();
  if (httpscode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpscode);
        String payload = client.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpscode);
      }
  client.end();
  Serial.println(n);
  delay(10000);
  n = (n+1) % 5;
}