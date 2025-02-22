/**************************
 * PID Control Testing Code for Strength Training System
 * 
 * This code implements a PID controller to adjust a motor output (via PWM)
 * based on a target force setpoint. Initially, the load cell reading is 
 * simulated. Replace the simulation code with your actual hardware code as 
 * needed.
 *
 * Hardware required (for full implementation):
 * - Load cell (with ADC module like HX711)
 * - Motor driver (controlled by PWM output)
 * - ESP32 or Arduino board
 *
 * Author: [Your Name]
 * Date: [Today's Date]
 **************************/

#include <PID_v1.h>  // Include Arduino PID Library

/** Pin Definitions **/
//const int MOTOR_PIN = 9;      // PWM output pin connected to your motor driver
                              // (Replace with your actual motor PWM pin)

/** PID Control Variables **/
double forceReading = 0.0;     // Input: Force measured by the load cell (kg)
double motorOutput  = 0.0;     // Output: PID controller output to drive motor (PWM value)
double targetResistance = 30.0; // Setpoint: Desired resistance (kg)
// Note: Replace targetResistance with a user-defined value if required

/** PID Tuning Parameters **/
// These are initial values; you will need to tune these (Kp, Ki, Kd) for your system.
double Kp = 2.0;
double Ki = 0.5;
double Kd = 1.0;

/** PID Controller Object **/
PID myPID(&forceReading, &motorOutput, &targetResistance, Kp, Ki, Kd, DIRECT);
// Use DIRECT direction since an increase in error should increase the motor output.

/**************************
 * Function: setup()
 * Purpose:  Initialize Serial communication, motor pin, and the PID controller.
 **************************/
void setup() {
  // Initialize serial communication for debugging and plotting
  Serial.begin(115200);

  // Set the motor PWM pin as output
  //pinMode(MOTOR_PIN, OUTPUT);

  // Initialize the PID controller in automatic mode
  myPID.SetMode(AUTOMATIC);
  
  // Set PID output limits to match PWM range (0-255 for 8-bit PWM)
  myPID.SetOutputLimits(0, 255);

  // (Optional) Print startup information
  Serial.println("PID Testing Code Initialized");
}

/**************************
 * Function: loop()
 * Purpose:  Simulate sensor reading, compute PID output, and apply PWM.
 **************************/
void loop() {
  // 1. Read force from the load cell (simulation mode)
  // Replace this function with your actual load cell reading function.
  forceReading = simulateLoadCell();

  // 2. Compute PID output
  myPID.Compute();

  // 3. Apply the PID output to the motor driver via PWM
  // Convert the double output to an integer value (0-255)
  //analogWrite(MOTOR_PIN, (int)motorOutput);

  // 4. Print values for debugging/graphing on the Serial Plotter
  // Format: time,forceReading,motorOutput

  Serial.print(forceReading, 2);      // Simulated force (kg)
  Serial.print(",");
  Serial.println(motorOutput, 2);       // PID output (PWM value)

  // 5. Small delay for loop stability (adjust as needed)
  delay(100);
}

/**************************
 * Function: simulateLoadCell()
 * Purpose:  Simulate a load cell reading for testing the PID algorithm.
 *           Replace this simulation with your actual sensor code.
 * Returns:  A simulated force value (kg).
 **************************/
double simulateLoadCell() {
  static double simulatedForce = 0.0;
  static unsigned long lastSimTime = 0;
  unsigned long currentTime = millis();
  double dt = (currentTime - lastSimTime) / 1000.0;  // Time difference in seconds
  lastSimTime = currentTime;

  // Simulate a ramp function: increase force gradually then reset at 50kg
  simulatedForce += dt * 2.0;  // Increase force by 2kg per second (adjust rate as needed)
  if(simulatedForce > 50.0) {
    simulatedForce = 0.0;  // Reset simulation after reaching 50kg
  }
  return simulatedForce;
}

/**************************
 * Notes for Hardware Implementation:
 * 1. Replace simulateLoadCell() with your actual load cell reading function,
 *    for example, using the HX711 library to read weight.
 * 2. Ensure that the targetResistance is set based on user input or testing
 *    requirements.
 * 3. Adjust PID gains (Kp, Ki, Kd) through testing (manual tuning or using an
 *    auto-tuning algorithm) to achieve smooth and stable control.
 * 4. Confirm that the motor driver accepts PWM signals on the specified MOTOR_PIN.
 * 5. Use the Arduino Serial Plotter (Tools > Serial Plotter) to visualize the
 *    force readings and PID output in real time.
 **************************/