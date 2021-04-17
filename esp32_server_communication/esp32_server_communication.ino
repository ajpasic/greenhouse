#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "credentials.h" /* make sure you add this file and that its contents are correct! */
#include "cmd_general.h"
#include "esp_camera.h"

//#define CAMERA_MODEL_WROVER_KIT
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

AsyncWebServer server(80);

/* FUNCTION IMPLEMENTATIONS */

void camera_init(void) {
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
  
  /* if PSRAM IC present, init with UXGA resolution and higher JPEG quality for larger pre-allocated frame buffer. */
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 20; // 0-63 lower number means higher quality
    config.fb_count = 2; // if more than one, i2s runs in continuous mode. Use only with JPEG
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 24; // 0-63 lower number means higher quality
    config.fb_count = 1; // if more than one, i2s runs in continuous mode. Use only with JPEG
  }

  #if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
  #endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

  #if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
  #endif

  Serial.println("Camera init successful");
}

/*
 * ARDUINO-SPECIFIC
 */

void setup() {
  Serial.begin(115200);

  camera_init();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
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

  server.on("/image", HTTP_GET, [](AsyncWebServerRequest *request) {
    camera_fb_t *picture = esp_camera_fb_get();
    if (!picture) {
      request->send(404); // camera capture failed
    }
    else {
      AsyncWebServerResponse *response = request->beginResponse(200, "image/jpeg", (const char *)picture->buf);
      response->addHeader("Access-Control-Allow-Origin", "*"); // allow resource sharing with any origin
      request->send(response);
    }
    
  });

  // start server
  server.begin();
}

void loop() {
  
}
