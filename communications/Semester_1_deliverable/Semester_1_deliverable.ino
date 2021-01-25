
//Defining Necessary Libraries
#include "esp_camera.h" //Library to access camera functionality of ESP32 CAM
#include "WiFi.h" //Library to connect to WiFi
#include "ESPAsyncWebServer.h" //Library for the ability to host a server
#include "credentials.h" // ssid and password

//Defining the pins for camera functionality on the ESP32 CAM AI-Thinker Model
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22


const char* ssid = "Maxwell’s iPhone";
const char* password = "maxwelljohn"; //No password is needed for my Wi-Fi

AsyncWebServer server(80); //creating an object of WebServer selecting HTTP port 80 which is default

const char HTML [] PROGMEM = R"rawliteral(
<!DOCTYPE html>
  <html>
  <head><meta charset="UTF-8"></head>
  <body>
  <h1>ESP32 Camera Server</h1>
  <form>
  <label for="temp">Temperature:</label><br>
  <input type="text" id="temp" name="temp"><br>
  <label for="light_time">Amount of Light Exposure Per Day (Hours):</label><br>
  <input type="text" id="light_time" name="light_time">
  <input type="submit" value="Submit">
  </form>
  <p> Current Image: </p>
  <img src="http://172.20.10.9/view_current_image" alt="ESP32CAM Current Image">
  </body>
  </html>)rawliteral";

void setup() {
//Camera Module OV2460 Initialization
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_XGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;
  //Selecting quality of image based on onboard resources

  // passing camera initialization structure to the camera initialization function
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  } 

  sensor_t * s = esp_camera_sensor_get();

  s->set_framesize(s, FRAMESIZE_XGA);

  //begin Server

  Serial.begin(115200); //setting the baud rate of the transmission

  WiFi.begin(ssid, password); //Begin connecting to the WiFi network
  
  Serial.print("Connecting to WiFi.");  // Communication to serial of WiFi progress & Aesthetics
  while(WiFi.status() != WL_CONNECTED) { // Until a connection is secured, remain in loop
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("ESP32 is now connected to WiFi"); // Confimation that connection was a success
  Serial.print("Local Server IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  //taking a photo and sending it to the server

  server.on("/view_current_image", HTTP_GET, [](AsyncWebServerRequest * request) {
 
    camera_fb_t * frame = NULL; //setting the pointer
    frame = esp_camera_fb_get(); //capturing the image using the ESP32 CAM library function

    //request->send(200, "text/plain", "hello");
    request->send_P(200, "image/jpeg", (const uint8_t *)frame->buf, frame->len);
      //send(HTTP staus codes, file type, what the file is)
 
    esp_camera_fb_return(frame);
  });
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", HTML);
  });

  /*server.on("/view_current_image", HTTP_GET, [](AsyncWebServerRequest * request) {
 
    camera_fb_t * frame = NULL; //setting the pointer
    frame = esp_camera_fb_get(); //capturing the image using the ESP32 CAM library function

    request->send(200, "text/plain", "hello");
    request->send_P(200, "image/jpeg", (const uint8_t *)frame->buf, frame->len);
      //send(HTTP staus codes, file type, what the file is)
 
    esp_camera_fb_return(frame);
  });
 
  /*server.begin();
  //Now configure the routes of the server
  
  server.on("/download_current_image", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(SPIFFS, "/test.jpg", "image/jpeg", true); //allows image to be downloaded as an attachment
    //            send(filing system, path to object, file type, will the file be downloaded or interpreted)
  });

  server.on("/view_current_image", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(SPIFFS, "/test.jpg", "image/jpeg", false); //allows image to be interpreted by the server
  });
  */
  server.begin(); //starting the server
  
  //take photo and send to server
}

void loop(){
  }
