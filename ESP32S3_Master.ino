#include <WiFi.h>
const char* ssid = "ESP32_Master_AP";
const char* password = "12345678";
const int port = 5000;
const int testDuration = 5000;

WiFiServer server(port);
WiFiClient client;

void setup() {
  Serial.begin(921600);
  delay(500);
  Serial.println("\n[MASTER] Starting WiFi AP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 6, false, 1);
  Serial.printf("[MASTER] AP IP: %s\n", WiFi.softAPIP().toString().c_str());
  server.begin(port);
  Serial.printf("[MASTER] Server listening on port %d\n\n", port);
}

void loop() {
  if (!client.connected()) {
    client = server.available();
    if (client) {
      Serial.println("[MASTER] Client connected!");
      client.setNoDelay(true);
      delay(500);
      testDownload();
      delay(500);
      testUpload();
    }
  }
}

void testDownload() {
  Serial.println("[TEST-DL] Sending data for 5 seconds...");
  unsigned long start = millis();
  unsigned long bytes = 0;
  char buffer[1024];
  
  while (millis() - start < testDuration) {
    bytes += client.write((uint8_t*)buffer, sizeof(buffer));
    client.flush();
  }
  
  unsigned long elapsed = millis() - start;
  float mbps = (bytes * 8.0) / (elapsed / 1000.0) / 1000000.0;
  Serial.printf("[TEST-DL] Result: %.2f Mbps (%.2f MB/s) - %.2f MB sent\n\n", mbps, mbps/8.0, bytes/(1024.0*1024.0));
}

void testUpload() {
  Serial.println("[TEST-UL] Receiving data for 5 seconds...");
  client.print("START_UPLOAD");
  unsigned long start = millis();
  unsigned long bytes = 0;
  char buffer[1024];
  
  while (millis() - start < testDuration) {
    if (client.available()) {
      bytes += client.readBytes((uint8_t*)buffer, sizeof(buffer));
    }
  }
  
  unsigned long elapsed = millis() - start;
  float mbps = (bytes * 8.0) / (elapsed / 1000.0) / 1000000.0;
  Serial.printf("[TEST-UL] Result: %.2f Mbps (%.2f MB/s) - %.2f MB received\n\n", mbps, mbps/8.0, bytes/(1024.0*1024.0));
  client.stop();
}