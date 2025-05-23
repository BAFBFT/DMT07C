#include "esp32-hal-ledc.h"

//Constants
const int motorPwmPin_power = 17;  
const int motorPwmPin_torque = 18;
const int motorDirectionPin = 19;
const int pwmChannel  = 0;  
const int pwmFreq     = 20000; 
const int pwmResolution = 8;   
const int potPin = 34;
const int BUTTON_PIN = 16;   // Button connected between pin 16 and GND

//Variables:
int potValue = 0; //save analog value

void setup(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up: reads HIGH when open, LOW when pressed
  
  Serial.begin(115200);
  
   // Configure pin mode for power pin
  pinMode(motorDirectionPin, OUTPUT);
  digitalWrite(motorDirectionPin, LOW);
  
  // Configure pin mode for power pin
  pinMode(motorPwmPin_power, OUTPUT);
  digitalWrite(motorPwmPin_power, HIGH);

  // Setup PWM channel and attach the speed control pin
  ledcAttach(motorPwmPin_torque, pwmFreq, pwmResolution);
}

void loop(){
  // Read pot, map to 0–255
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 4095, 0, 255);

    
  if (digitalRead(BUTTON_PIN) == LOW) {
    // → RUN
    ledcWrite(pwmChannel, potValue);        // set torque
    Serial.println(potValue);
  }
  
  else { //Stop MOTOR
  // → STOP
    ledcWrite(pwmChannel, 0);               // zero PWM

  }

  //ledcWrite(motorPwmPin_torque, potValue); 
  delay(15);
}