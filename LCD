#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Most backpacks default to 0x27.  Run an I²C-scanner if unsure.
LiquidCrystal_I2C lcd(0x27, 16, 2);   // addr, cols, rows

void setup() {
  Wire.begin(4, 5);        // SDA, SCL pins on the ESP32
  lcd.init();              // initialise the LCD
  lcd.backlight();         // turn on the LED back-light

  lcd.setCursor(0, 0);     // column 0, row 0
  lcd.print("Hello, world!");
}

void loop() {
  /* nothing to do */
}
