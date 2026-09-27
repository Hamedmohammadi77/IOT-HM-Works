# 🖥️ Exercise 4 — TFT Display + Fading Text Animation

← [Back to Main](../../README.md)

---

## 📖 Description

This exercise drives a **1.8" ST7735 TFT display** over SPI and implements a custom **fading text animation**.

Each message appears on the screen in white, stays visible for 2 seconds, and then gradually fades out to black. After a short delay, the next message is displayed.

The sequence continues indefinitely in a loop.

---

## 🛠️ Hardware Required

| Component  | Details         |
| ---------- | --------------- |
| Board      | ESP32-S3        |
| Display    | ST7735 TFT 1.8" |
| Resolution | 128×160         |
| Interface  | SPI             |
| CS         | GPIO `10`       |
| DC         | GPIO `9`        |
| RST        | GPIO `8`        |
| SCLK       | GPIO `12`       |
| MOSI       | GPIO `11`       |

---

## 📚 Libraries Used

| Library           | Purpose                     |
| ----------------- | --------------------------- |
| `Adafruit_GFX`    | Graphics and text rendering |
| `Adafruit_ST7735` | ST7735 TFT display driver   |
| `SPI.h`           | SPI communication           |

---

## 📋 How It Works

### Setup

The `setup()` function runs once when the ESP32 starts:

* Initializes Serial communication at `115200` baud
* Initializes the ST7735 display using `INITR_BLACKTAB`
* Sets the display rotation to landscape (`1`)
* Clears the entire screen with black

```cpp
tft.initR(INITR_BLACKTAB);
tft.setRotation(1);
tft.fillScreen(ST77XX_BLACK);
```

---

### `showFadingText(text)`

The main animation is handled by:

```cpp
showFadingText("Your message here");
```

The function performs the following steps:

**1. Display the text**

The message is printed in white at position `(10, 50)`.

**2. Keep the text visible**

The message remains fully visible for **2 seconds**.

**3. Fade the text**

The brightness is gradually reduced from `255` to `0`.

For every step, the program:

* Erases the previous version of the text
* Calculates a new grey color
* Draws the text again
* Waits `25ms`

The color is generated using:

```cpp
uint16_t color = tft.color565(
    brightness,
    brightness,
    brightness
);
```

**4. Erase the text**

After the fade finishes, the text is completely removed by drawing it in black.

---

## 🔄 Loop

The `loop()` function displays several messages sequentially.

Each message:

1. Appears in white
2. Remains visible for 2 seconds
3. Fades out
4. Waits for 1 second
5. Displays the next message

The sequence then repeats forever.

---

## 📝 Messages

The sketch can display any custom messages. For example:

```text
[Message 1]

[Message 2]

[Message 3]

[Message 4]

[Message 5]
```

The messages are defined directly inside the `loop()` function:

```cpp
showFadingText("[Message 1]");
delay(1000);

showFadingText("[Message 2]");
delay(1000);

showFadingText("[Message 3]");
delay(1000);
```

Replace the placeholders with any text you want to display.

---

## 🚀 How to Run

1. Open the `.ino` file in **Arduino IDE**.
2. Install the required libraries through:
   **Tools → Manage Libraries**
3. Install:

   * `Adafruit ST7735 and ST7789 Library` by Adafruit
   * `Adafruit GFX Library` by Adafruit
4. Select:
   **ESP32S3 Dev Module**
5. Connect the TFT according to the wiring table.
6. Upload the sketch.
7. Watch the messages appear and fade out.

---

## ⚠️ Notes

* `tft.setTextSize(1.5)` does **not** produce a 1.5× text size. The Adafruit GFX API expects an integer text size, so `1.5` is converted to `1`.
* Use `tft.setTextSize(2)` or another integer value if you want larger text.
* The fade effect is simulated by repeatedly redrawing the text with progressively darker grey colors.
* The ST7735 does not provide transparency-based text fading, so the animation is implemented manually.
* The fade loop uses `15` brightness steps with a `25ms` delay, resulting in roughly **450ms** of fade time.
* Long messages may exceed the available screen width because this sketch does not currently implement automatic text wrapping or scrolling.
* The display is configured with rotation `1`, so the effective screen orientation is landscape.

---

## 💡 Possible Improvements

Future versions of this exercise could add:

* Fade-in + fade-out animation
* Automatic text centering
* Automatic text wrapping
* Text scrolling
* Multiple text colors
* Different font sizes
* Typewriter animation
* Reading messages from an SD card
* Displaying GIF animations
* Wi-Fi controlled messages
* Web interface for sending messages to the TFT
* Sound effects synchronized with the animation
