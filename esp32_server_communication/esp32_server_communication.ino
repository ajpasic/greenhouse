#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"

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

uint8_t convertASCIItoInteger(uint8_t *data, size_t len) {
  uint8_t value = 0;
  for (int i = 0; i < len; i++) {
    uint8_t increment = (data[i] - '0') * pow(10, len-1 - i);
    value += increment;
  }
  return value;
}

void uart_init(void) {
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  uart_param_config(UART_NUM_1, &uart_config);
  uart_set_pin(UART_NUM_1, 14, 2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_NUM_1, 512*2, 512*2, 0, NULL, 0);
  uart_flush(UART_NUM_1);
}

void cmd_transmit(cmd_noun_t noun, cmd_verb_t verb, uint8_t *dataArray, uint8_t setpoint = 0x00) {
  uint8_t result = 0;
  uint8_t cmd_message[7];
  if (noun < SIZE_OF_NOUN_TABLE && verb < SIZE_OF_VERB_TABLE) {
    cmd_message[0] = (uint8_t) noun;
    cmd_message[1] = (uint8_t) verb;
    cmd_message[2] = setpoint;
    cmd_message[6] = 0xFF;
  }
  
  uart_write_bytes(UART_NUM_1, (const char*) cmd_message, 7);
  uart_wait_tx_done(UART_NUM_1, 100);
  uart_read_bytes(UART_NUM_1, dataArray, 7, 100);
  uart_flush(UART_NUM_1);
}

/*
 * ARDUINO SPECIFIC
 */

void setup() {
  Serial.begin(115200);

  //camera_init();
  uart_init();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nESP32 connected at IP address ");
  Serial.println(WiFi.localIP());

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) {
    uint8_t temperature, humidity, water, light;
    uint8_t arr[7];

    cmd_transmit(TEMPERATURE, GET, arr);
    temperature = arr[2];

    // get humidity from Tiva C
    cmd_transmit(HUMIDITY, GET, arr);
    humidity = arr[2];

    cmd_transmit(WATERING, GET, arr);
    water = arr[2];

    cmd_transmit(LIGHTING, GET, arr);
    light = arr[2];
    
    String JSONresponse = String("{\"temperature\":\"") + String(temperature) + String("\",");
    JSONresponse += String("\"humidity\":\"") + String(humidity) + String("\",");
    JSONresponse += String("\"water\":\"") + String(water) + String("\",");
    JSONresponse += String("\"light\":\"") + String(light) + String("\"}");
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", JSONresponse);
    response->addHeader("Access-Control-Allow-Origin", "*"); // allow resource sharing with any origin
    request->send(response);
  });

  server.on("/temperature", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL,
  [](AsyncWebServerRequest *request, uint8_t *dataArray, size_t len, size_t index, size_t total) {
    // temperature setpoint
    uint8_t value = convertASCIItoInteger(dataArray, len);
    Serial.println(value);

    uint8_t arr[7];
    cmd_transmit(TEMPERATURE, SET, arr, value);
    
    AsyncWebServerResponse *response = request->beginResponse(200);
    response->addHeader("Access-Control-Allow-Origin", "*"); // allow resource sharing with any origin
    request->send(response);
  });

  server.on("/humidity", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL,
  [](AsyncWebServerRequest *request, uint8_t *dataArray, size_t len, size_t index, size_t total) {
    // humidity setpoint
    uint8_t value = convertASCIItoInteger(dataArray, len);
    Serial.println(value);

    uint8_t arr[7];
    cmd_transmit(HUMIDITY, SET, arr, value);
    
    AsyncWebServerResponse *response = request->beginResponse(200);
    response->addHeader("Access-Control-Allow-Origin", "*"); // allow resource sharing with any origin
    request->send(response);
  });

  server.on("/light", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL,
  [](AsyncWebServerRequest *request, uint8_t *dataArray, size_t len, size_t index, size_t total) {
    // light setpoint
    uint8_t value = convertASCIItoInteger(dataArray, len);
    Serial.println(value);

    uint8_t arr[7];
    cmd_transmit(LIGHTING, SET, arr, value);
    
    AsyncWebServerResponse *response = request->beginResponse(200);
    response->addHeader("Access-Control-Allow-Origin", "*"); // allow resource sharing with any origin
    request->send(response);
  });

  server.on("/water", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL,
  [](AsyncWebServerRequest *request, uint8_t *dataArray, size_t len, size_t index, size_t total) {
    // water setpoint
    uint8_t value = convertASCIItoInteger(dataArray, len);
    Serial.println(value);

    uint8_t arr[7];
    cmd_transmit(WATERING, SET, arr, value);
    
    AsyncWebServerResponse *response = request->beginResponse(200);
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
