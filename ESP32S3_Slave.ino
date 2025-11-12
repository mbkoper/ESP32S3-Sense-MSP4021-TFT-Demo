// ESP32S3 Slave WiFi Client Device Example

#include <WiFi.h>

const char* ssid = "your_SSID";  // Replace with your network SSID
const char* password = "your_PASSWORD";  // Replace with your network password

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    // Speed test code goes here
    // For example, send a GET request to a server and measure response time

    // Simulate doing a speed test (this would need real implementation for full functionality)
    long startTime = millis();
    WiFiClient client;
    if (client.connect("example.com", 80)) {
        client.print("GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n");
        while (client.connected() && !client.available()) {
            delay(100);
        }
        while(client.available()) {
            String line = client.readStringUntil('\n');
            Serial.println(line);
        }
    }
    long elapsedTime = millis() - startTime;
    Serial.printf("Speed Test Duration: %ld ms\n", elapsedTime);
    client.stop();

    delay(10000);  // Wait 10 seconds before next test
}