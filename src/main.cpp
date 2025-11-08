#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "esp_camera.h"

// ----- Configure these to match your wiring -----
#define TOUCH_CS_PIN 14   // XPT2046 CS
#define TOUCH_IRQ_PIN 7   // XPT2046 IRQ (optional)

// TFT_eSPI will pick up settings from lib/TFT_eSPI/User_Setup.h in this project
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(TOUCH_CS_PIN);

// === Camera configuration ===
// NOTE: Verify the exact camera pin mapping for your XIAO ESP32S3 Sense variant.
// The mapping here is illustrative and must be adapted to your board's documentation.
void setupCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  // Example pins - update these to match your board
  config.pin_d0 = 15;
  config.pin_d1 = 17;
  config.pin_d2 = 18;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 38;
  config.pin_pclk = 33;
  config.pin_vsync = 40;
  config.pin_href = 41;
  config.pin_sccb_sda = 8;  // SCCB/SDA (I2C for camera)
  config.pin_sccb_scl = 9;
  config.pin_pwdn = 10;
  config.pin_reset = -1;     // if board provides a camera reset pin, set it here

  config.xclk_freq_hz = 20000000; // 20MHz typical, adjust if needed
  config.pixel_format = PIXFORMAT_RGB565; // RGB565 preferred for direct pushImage
  config.frame_size = FRAMESIZE_QVGA;     // 320x240 - fits 480x320 display after centering/scaling
  config.jpeg_quality = 10;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
  } else {
    Serial.println("Camera initialized");
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  // TFT init
  tft.init();
  tft.setRotation(1); // adjust rotation (0-3) until image orientation is ok
  tft.fillScreen(TFT_BLACK);

  // Touch init
  if (!ts.begin()) {
    Serial.println("Touchscreen init failed!");
  }
  ts.setRotation(1);

  // Camera init
  setupCamera();

  tft.setTextSize(2);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(20, 20);
  tft.println("MSP4021 + ESP32S3!");
}

// Simple helper to display camera frame (if camera gives RGB565)
void displayCameraFrame() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) return;

  // If fb->format == PIXFORMAT_RGB565, fb->buf is an RGB565 buffer
  // If JPEG, you must decode JPEG to RGB565 before pushImage
  if (fb->format == PIXFORMAT_RGB565) {
    // Example: center a 320x240 frame on the 480x320 display
    int img_w = fb->width;
    int img_h = fb->height;
    int x = (tft.width() - img_w) / 2;
    int y = (tft.height() - img_h) / 2;
    tft.pushImage(x, y, img_w, img_h, (uint16_t*)fb->buf);
  } else {
    // For JPEG frames, you need a JPEG decoder (not included in this example)
    Serial.println("Camera frame not in RGB565 format: decode required");
  }

  esp_camera_fb_return(fb);
}

void loop() {
  static int x = 0;
  static int dx = 2;

  // Moving box demo
  tft.fillRect(x, 200, 40, 40, TFT_GREEN);
  delay(30);
  tft.fillRect(x, 200, 40, 40, TFT_BLACK);
  x += dx;
  if (x < 0 || x > tft.width() - 40) dx = -dx;

  // Touch demo
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    // Map or swap axes if needed depending on rotation and touch wiring
    int tx = p.x;
    int ty = p.y;
    // NOTE: Raw touch coordinates often need mapping to screen coordinates.
    // Example mapping (uncomment and adapt if needed):
    // tx = map(p.y, 0, 4095, 0, tft.width());
    // ty = map(p.x, 0, 4095, 0, tft.height());
    tft.fillCircle(tx, ty, 8, TFT_RED);
  }

  // Camera display demo (uncomment to enable)
  // displayCameraFrame();
}