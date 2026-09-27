#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8

#define TFT_SCLK 12
#define TFT_MOSI 11

Adafruit_ST7735 tft = Adafruit_ST7735(
    TFT_CS,
    TFT_DC,
    TFT_MOSI,
    TFT_SCLK,
    TFT_RST
);

void showFadingText(const char* text)
{
    int x = 10;
    int y = 50;

    // نمایش متن
    tft.setTextSize(1.5);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(x, y);
    tft.print(text);

    // 2 ثانیه نمایش کامل
    delay(2000);

    // محو شدن
    for (int brightness = 255; brightness >= 0; brightness -= 15)
    {
        uint16_t color = tft.color565(
            brightness,
            brightness,
            brightness
        );

        // پاک کردن متن قبلی
        tft.setTextColor(ST77XX_BLACK);
        tft.setCursor(x, y);
        tft.print(text);

        // رسم با روشنایی جدید
        tft.setTextColor(color);
        tft.setCursor(x, y);
        tft.print(text);

        delay(25);
    }

    // پاک کردن کامل
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(x, y);
    tft.print(text);
}

void setup()
{
    Serial.begin(115200);

    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);

    tft.fillScreen(ST77XX_BLACK);
}

void loop()
{
    showFadingText("the world fuck me!!");
    delay(1000);

    showFadingText("university fuck me");
    delay(1000);

    showFadingText("this fucking headache fuck me");
    delay(1000);

    showFadingText("and also these motherfuckers peaple");
    delay(1000);

    showFadingText("look buddy it is true i am fucked up but i am standing ,i am standing fucked up man , yeeeeeeeehhhh?><!!!!");
    delay(1000);
}