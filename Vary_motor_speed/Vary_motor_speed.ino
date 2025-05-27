// Constants
#define motorPwmPin_power 26
#define motorPwmPin_torque 27
#define motorDirectionPin 25
#define potPin 34
#define buttonPin 16 // Assign your button to GPIO 16 

#define pwmChannel 0
#define pwmFreq 20000
#define pwmResolution 8

// Variables
volatile bool motorOn = false; // Motor starts OFF
int potValue = 0;

void setup() {

  // Configure pins
  pinMode(motorDirectionPin, OUTPUT);
  digitalWrite(motorDirectionPin, LOW);
  pinMode(motorPwmPin_power, OUTPUT);
  digitalWrite(motorPwmPin_power, HIGH); // Motor driver ON
  pinMode(buttonPin, INPUT); // Button with pull-up

  // Attach PWM
  ledcAttach(motorPwmPin_torque, pwmFreq, pwmResolution);
}

void loop() {
  static bool lastButtonState = HIGH;            // remembered value
  bool buttonState = digitalRead(buttonPin);    // current value

  if (buttonState == LOW && lastButtonState == HIGH)  // edge detected
  {
    motorOn = !motorOn;         // toggle motor state
    delay(50);                  // crude bounce soak-time (optional)
  }
  lastButtonState = buttonState;

  if (motorOn) {
    potValue = analogRead(potPin);
    potValue = map(potValue, 0, 4095, 0, 255); // Map to PWM range
  } else {
    potValue = 0; // Force motor off
  }

  ledcWrite(motorPwmPin_torque, potValue);
  delay(15);
  Serial.println(potValue);
}
