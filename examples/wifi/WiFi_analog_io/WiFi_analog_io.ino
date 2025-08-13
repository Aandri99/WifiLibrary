// Example showing how to use RP SCPI API over WiFi.
// Connect Arduino R4 WiFi to a Red Pitaya board via TCP.

#include <WiFiS3.h>

#include "SCPI_RP.h"

char ssid[] = "YOUR_SSID";           // your network SSID
char pass[] = "YOUR_PASSWORD";       // your network password
IPAddress server(192, 168, 1, 100);  // Red Pitaya IP

WiFiClient client;

scpi_rp::SCPIRedPitaya rp;

bool isInit = false;
float value = 0;

void setup() {
  Serial.begin(115200);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(10000);
  }

  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(server, 5000)) {
    Serial.println("Connected to Red Pitaya");
    rp.initClient(&client);
    isInit = true;
  } else {
    Serial.println("Connection failed");
  }
}

void loop() {
  if (isInit) {
    float in_value = 0;
    if ((value * 10) > 18) value = 0;
    if (!rp.aio.state(scpi_rp::AOUT_0, value)) {
      Serial.println("Error set value");
    }
    if (!rp.aio.stateQ(scpi_rp::AOUT_0, &in_value)) {
      Serial.println("Error get value");
    }
    Serial.print("AOUT_0 value = ");
    Serial.println(in_value);
    if (!rp.aio.stateQ(scpi_rp::AIN_0, &in_value)) {
      Serial.println("Error get value");
    }
    Serial.print("AIN_0 value = ");
    Serial.println(in_value);
    delay(1000);
    value += 0.1;
  }
}
