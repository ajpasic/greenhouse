#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "commands.h"

const char* ssid = "71000Sarajevo";
const char* password = "!Pasword1#";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    //delay(1000);
  }
  Serial.print("\nESP32 connected at IP address ");
  Serial.println(WiFi.localIP());

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    unsigned int temperature = random(60, 81);
    String JSONresponse = String("{\"temperature\":\"") + String(temperature) + String("\"}");
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", JSONresponse);
    response->addHeader("Access-Control-Allow-Origin", "*"); // allow resource sharing with any origin

    
    
    request->send(response);
  });

  // start server
  server.begin();
}

void loop() {
  
}
