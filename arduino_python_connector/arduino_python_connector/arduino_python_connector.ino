#include "WiFi.h"
#include "ESPAsyncWebServer.h"
const char* ssid = "dandannoodles";
const char* password =  "carinaisanalcoholic";
AsyncWebServer server(80);
int relayPin = 23;
bool alarm_go = false;
void setup()
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  server.on("/alarm", HTTP_GET, [](AsyncWebServerRequest * request) {

    if (!alarm_go) {
      request->send(200, "text/plain", "open");
    } 

  });

  server.on("/locate/bag", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Your bag is located at St.DanDan");
  });

  server.on("/dismiss", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "ok");
    digitalWrite(relayPin, LOW);
  });

  server.begin();
}
void loop() {}
