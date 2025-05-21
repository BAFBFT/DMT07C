#include <Wire.h>
#include <LiquidCrystal_I2C.h>

constexpr uint8_t SDA_PIN = 4;          // your wiring
constexpr uint8_t SCL_PIN = 5;
constexpr uint8_t I2C_ADDR = 0x27;      // change if your backpack scans to a different address

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2); // addr, cols, rows

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);  // override ESP32 default I²C pins
  lcd.init();
  lcd.backlight();
}

void loop() {
  static uint8_t count = 1;      // start at 1

  // draw 
  lcd.setCursor(0, 0);
  lcd.print(F("Count:     "));   // pad with spaces so old digits get overwritten
  lcd.setCursor(7, 0);
  lcd.print(count);

  // prepare next iteration 
  if (++count > 100) {
    // comment the next line if you want to wrap and count forever
    while (true) yield();        // freeze at 100
    // or, to loop: count = 1;
  }

  delay(500);                    // 0.5 s between updates
}
