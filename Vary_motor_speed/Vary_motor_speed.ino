#include "esp32-hal-ledc.h"

const int motorPwmPin_power = 17;  
const int motorPwmPin_speed = 18;
const int motorDirectionPin = 19;
const int pwmChannel  = 0;  
const int pwmFreq     = 20000; 
const int pwmResolution = 8;   

void setup(){
    // Configure pin mode for power pin
  pinMode(motorDirectionPin, OUTPUT);
  digitalWrite(motorDirectionPin, LOW);
  
  // Configure pin mode for power pin
  pinMode(motorPwmPin_power, OUTPUT);
  digitalWrite(motorPwmPin_power, HIGH);

  // Setup PWM channel and attach the speed control pin
  ledcAttach(motorPwmPin_speed, pwmFreq, pwmResolution);
}

void loop(){
  // Increase the brightness (or motor speed)
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(pwmChannel, dutyCycle);
    delay(15);
  }
  // Decrease the brightness (or motor speed)
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(pwmChannel, dutyCycle);   
    delay(15);
  }
}
