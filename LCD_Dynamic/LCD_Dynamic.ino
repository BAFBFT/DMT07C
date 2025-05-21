#include <Wire.h>
#include <LiquidCrystal_I2C.h>

constexpr uint8_t SDA_PIN   = 4;     // I²C data  (ESP32 GPIO 4)
constexpr uint8_t SCL_PIN   = 5;     // I²C clock (ESP32 GPIO 5)
constexpr uint8_t I2C_ADDR  = 0x27;  // PCF8574 backpack address
constexpr uint8_t POT_PIN   = 34;    // ADC1_CH6 -- wiper of the pot

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);   // use your custom I²C pins
  lcd.init();
  lcd.backlight();

  analogReadResolution(12);       // 0-to-4095 (ESP32 default, but explicit is nice)
  lcd.setCursor(0, 0);
  lcd.print(F("Potentiometer:"));
}

void loop() {
  int raw = analogRead(POT_PIN);          // 0 … 4095
  int pct = map(raw, 0, 4095, 0, 100);    // convert to %

  /* overwrite the 2nd line cleanly */
  lcd.setCursor(0, 1);
  lcd.print("        ");               // 8 spaces to erase previous text
  lcd.setCursor(0, 1);
  lcd.print(pct);
  lcd.print("%");                      // e.g. “53%”

  delay(100);                             // refresh ~10×/s
}
