#include "esp32-hal-ledc.h"

//Constants
const int motorPwmPin_power = 17;  
const int motorPwmPin_torque = 18;
const int motorDirectionPin = 19;
const int pwmChannel  = 0;  
const int pwmFreq     = 20000; 
const int pwmResolution = 8;   
const int potPin = 22;


//Variables:
int potValue = 0; //save analog value

void setup(){
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
    potValue = analogRead(potPin);
    //Vary torque using ledcWrite
    potValue = map(potValue, 0, 4095, 0, 255); //Map value 0-4095 to 0-255 (PWM)
    
    ledcWrite(motorPwmPin_torque, potValue);   
    delay(15); //small delay for stability
    Serial.println(potValue);
}
