#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 14;

HX711 scale;

// LCD circuit wiring

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

constexpr uint8_t SDA_PIN   = 4;     // I²C data  (ESP32 GPIO 4)
constexpr uint8_t SCL_PIN   = 5;     // I²C clock (ESP32 GPIO 5)
constexpr uint8_t I2C_ADDR  = 0x27;  // PCF8574 backpack address
constexpr uint8_t POT_PIN   = 34;    // ADC1_CH6 -- wiper of the pot

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

void setup() {
  //LCD SETUP
  Wire.begin(SDA_PIN, SCL_PIN);   // use your custom I²C pins
  lcd.init();
  lcd.backlight();

  analogReadResolution(12);       // 0-to-4095 (ESP32 default, but explicit is nice)
  lcd.setCursor(0, 0);
  lcd.print("Loadcell Reading:");

  //LOADCELL SETUP
  Serial.begin(115200);
  rtc_cpu_freq_config_t config;
  rtc_clk_cpu_freq_get_config(&config);
  rtc_clk_cpu_freq_set_config_fast(&config);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
            
  scale.set_scale(47000);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);

  //PRINT TO LCD
  lcd.setCursor(0, 1);
  lcd.print(scale.get_units(), 1);
 

  scale.power_down();             // put the ADC in sleep mode
  scale.power_up();
}

//______________________//

/*

void loop() {
  int raw = analogRead(POT_PIN);          // 0 … 4095
  int pct = map(raw, 0, 4095, 0, 100);    // convert to %

  overwrite the 2nd line cleanly 
  lcd.setCursor(0, 1);
  lcd.print("        ");               // 8 spaces to erase previous text
  lcd.setCursor(0, 1);
  lcd.print(pct);
  lcd.print("%");                      // e.g. “53%”

  delay(100);                             // refresh ~10×/s
}*/
