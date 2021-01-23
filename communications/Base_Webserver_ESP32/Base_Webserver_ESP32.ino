//Server Development
//(HTTP)- Hypertext Transfer Protocl
//When a request is sent to the server (ex: its address is searched in the browser), the server returns a code as a response (ex: code 200, if a connection is established, and code 404 if the address is incorrect or not found)

#include <WiFi.h>
#include <WebServer.h>

//Wifi Connection init

  //defining credentials
const char* ssid = "CambridgeOaks-Residents";
const char* password = ""; //not needed because device is registered through MAC address

WebServer server(80); //creating an object of WebServer selecting HTTP port 80 which is default

void setup() {
  
  Serial.begin(115200); //Begin serial communication with a baud/symbol rate of 115200

  WiFi.begin(ssid, password); // Begin connecting to Wifi

  Serial.print("Connecting to WiFi.");  // Communication to serial of WiFi progress
  
  while(WiFi.status() != WL_CONNECTED) { // Until a connection is secured, remain in loop
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("ESP32 is now connected to WiFi"); // Confimation that connection was a success
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_root); //This adds a '/' after the address in the browser after the main address is searched and then calls the handle_root function 
  
  server.begin(); //Start the server
  Serial.println("HTTP server started");
  delay(100); 
}

void loop() {
  server.handleClient();
}

// HTML and CSS code in order to display text and have functionality on the server
// HTML uses tags <>. All HTML code should be placed between these tags
// CSS (Cascading Style Sheets) commands specify how HTML code and instructions are displayed to the user

              // HTML and CSS intro

// The <!DOCTYPE html> command announces to the browser which type of HTML you used to write the page
// Immediately after this line of code, all subsequent code should be encased in <html> tags
// The <h1> through <h6> commands create headlines in different sizes
// use tags <p> ...</p> to create individual paragraphs
// use <> to begin a line and </> to end it
// <b> is for bold text
// <a href=inputlinkhere> nameoflink</a> is for creating a link
// for images <img src="link" alt = nameofimage width=* height=*>
// for buttons <button type="" onclick="alert(function)">Nameofbutton</button>
// <style>... </style> is used to style the text or button you are displaying, put all stylers inside these tags
// <div> creates a section in the code

String HTML = "<!DOCTYPE html>\ 
  <html>\
  <head><meta charset=\"UTF-8\"></head>\
  <body>\
  <h1>ESP32 Camera Server</h1>\
  <p> Hello! This server is still under development... </p>\
  </body>\
  </html>";

// Handle Root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
