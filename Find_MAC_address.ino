#include <WiFi.h>
#include "esp_wifi.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.begin();
  Serial.print("MAC address: "); Serial.println(WiFi.macAddress());
}


void loop() {

}
