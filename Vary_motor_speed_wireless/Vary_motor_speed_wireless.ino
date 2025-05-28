#include <esp_now.h>
#include <WiFi.h>

// Constants
#define motorPwmPin_power 26
#define motorPwmPin_torque 27
#define motorDirectionPin 25
#define buttonPin 16

#define pwmFreq 20000
#define pwmResolution 8

typedef struct struct_message {
  int potValue;
} struct_message;

struct_message myData;

// Updated callback for ESP-NOW v5+
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  int pwmValue = constrain(myData.potValue, 0, 255);
  ledcWrite(0, pwmValue);  // Channel 0 for torque
  Serial.print("Received potValue: ");
  Serial.println(pwmValue);
}

void setup() {
  Serial.begin(115200);

  // Configure motor pins
  pinMode(motorDirectionPin, OUTPUT);
  digitalWrite(motorDirectionPin, LOW);
  pinMode(motorPwmPin_power, OUTPUT);
  digitalWrite(motorPwmPin_power, HIGH);
  pinMode(buttonPin, INPUT);

  // Attach PWM
  ledcAttach(motorPwmPin_torque, pwmFreq, pwmResolution);
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing needed here
}
