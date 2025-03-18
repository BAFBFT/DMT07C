// Define PWM output and analog input pins
const int pwmOutPin = 9;       // PWM output on digital pin 9 (adjust as needed for your ESP32 board)
const int analogPin = 36;      // Analog input from the potentiometer (GPIO36 is a common ADC pin on ESP32)

// PWM configuration parameters
const int pwmFreq = 5000;      // PWM frequency in Hz
const int pwmChannel = 0;      // PWM channel (ESP32 supports channels 0-15)
const int pwmResolution = 8;   // PWM resolution (8-bit: values range from 0 to 255)

void setup() {
  // Initialize the PWM functionality on the ESP32 using the LEDC module.
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  // Attach the PWM channel to the output pin.
  ledcAttachPin(pwmOutPin, pwmChannel);
}

void loop() {
  // Read the analog value from the potentiometer (default range 0-4095 on ESP32)
  int sensorValue = analogRead(analogPin);
  // Map the analog value to the PWM range (0-255)
  int pwmValue = map(sensorValue, 0, 4095, 0, 255);
  // Write the PWM value to the output pin using the LEDC channel
  ledcWrite(pwmChannel, pwmValue);
  
  delay(10);  // Optional
  3.small delay for stability
}
