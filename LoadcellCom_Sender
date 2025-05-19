#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "HX711.h"

// HX711 pins
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN  = 4;
HX711 scale;

// ESP32 receiver MAC address (replace with your receiver’s MAC)
uint8_t receiverMAC[] = { 0xD0, 0xEF, 0x76, 0x47, 0xF7, 0x44 };

// Data structure to send: one float representing weight units
typedef struct struct_message {
  float weight;
} struct_message;

struct_message msg;

// Send callback: print send status
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send to ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.print(" -> ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);

  // Initialize HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(47000);  // Adjust to your calibration factor
  scale.tare();

  // Configure as Wi-Fi station and disconnect
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    while (true) { delay(1000); }
  }

  // Register send callback
  esp_now_register_send_cb(OnDataSent);

  // Add receiver as a peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    while (true) { delay(1000); }
  }

  Serial.println("Sender ready, sending 1 reading/sec");
}

void loop() {
  // Read average weight once per second
  float avg = scale.get_units(10);
  msg.weight = avg;

  // Send the message
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&msg, sizeof(msg));
  if (result != ESP_OK) {
    Serial.println("Error: esp_now_send failed");
  } else {
    // Detailed status printed in OnDataSent callback
    Serial.print("Sent weight: ");
    Serial.println(avg, 3);
  }

  delay(1000);
}
