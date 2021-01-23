#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "index.h"  // Web page header file
#include "credentials.h" // SSID and password

#define LEDPin 15 // LED connected to GPIO pin 15

WebServer server(80);

void handleRoot() {
  // executed when you open its IP in browser
  String s = MAIN_page; // read html content
  server.send(200, "text/html", s); //Send web page
}
 
void toggleLED() {
  Serial.println("toggleLED called");
  // Toggle
  pinMode(LEDPin, INPUT);
  int current = digitalRead(LEDPin);
  pinMode(LEDPin, OUTPUT);
  current ^= 1;
  digitalWrite(LEDPin, current);
  
  // Send new value back to client
  String on_off;
  if (current == 0) {
    on_off = "off";
  } else {
    on_off = "on";
  }
  server.send(200, "text/plane", on_off);
}

void setup(void) {
  // set pin 15 as low output
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

/*
//ESP32 As access point
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);
*/
  // ESP32 connects to your wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  // Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED) {      
    Serial.print(".");
  }
    
  // If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());     // IP address assigned to your ESP

  server.on("/", handleRoot);         // This is display page
  server.on("/toggleLED", toggleLED); // LED toggle page
 
  server.begin();                     // Start server
  Serial.println("HTTP server started");
}

void loop(void) {
  // This routine is executed when you open its IP in browser
  server.handleClient();
}
