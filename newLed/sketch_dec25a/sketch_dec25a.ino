#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

// =====================
// LCD 1602 I2C
// =====================
#define SDA_PIN 8
#define SCL_PIN 9

LiquidCrystal_I2C lcd(0x27, 16, 2);

// =====================
// RGB NeoPixel
// =====================
#define LED_PIN 48
#define LED_COUNT 1 

Adafruit_NeoPixel led(
  LED_COUNT,
  LED_PIN,
  NEO_GRB + NEO_KHZ800
);

void setup() {

  // =====================
  // LED
  // =====================
  led.begin();
  led.setBrightness(25);
  led.clear();
  led.show();

  // =====================
  // LCD
  // =====================
  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello!");

  lcd.setCursor(0, 1);
  lcd.print("ESP32-S3");
}

void loop() {

  // 🔴 Red
  led.setPixelColor(0, led.Color(255, 0, 0));
  led.show();

  delay(1000);

  // 🟢 Green
  led.setPixelColor(0, led.Color(0, 255, 0));
  led.show();

  delay(1000);

  // 🔵 Blue
  led.setPixelColor(0, led.Color(0, 0, 255));
  led.show();

  delay(1000);

  // خاموش
  led.clear();
  led.show();

  delay(1000);
}