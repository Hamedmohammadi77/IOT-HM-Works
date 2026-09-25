# 💡 Exercise 1 — RGB LED + LCD Display

← [Back to Main](../../README.md)

---

## 📖 Description

This exercise controls an onboard **NeoPixel RGB LED** on an **ESP32-S3** while displaying a welcome message on a **1602 LCD screen over I2C**. The LED cycles through Red → Green → Blue → Off with a 1-second delay between each state.

---

## 🛠️ Hardware Required

| Component | Details |
|-----------|---------|
| Board | ESP32-S3 |
| RGB LED | NeoPixel (pin `48`, 1 LED) |
| Display | LCD 1602 with I2C backpack (address `0x27`) |
| Connection | I2C — SDA: pin `8`, SCL: pin `9` |

---

## 📚 Libraries Used

| Library | Purpose |
|---------|---------|
| `Wire.h` | I2C communication |
| `LiquidCrystal_I2C` | LCD control |
| `Adafruit_NeoPixel` | RGB LED control |

---

## 📋 How It Works

**Setup (runs once):**
- Initializes the NeoPixel LED at brightness `25/255` and clears it
- Starts I2C on pins 8 (SDA) and 9 (SCL)
- Initializes the LCD, turns on the backlight
- Prints `"Hello!"` on row 1 and `"ESP32-S3"` on row 2

**Loop (repeats forever):**

```
🔴 Red  (1s) → 🟢 Green (1s) → 🔵 Blue (1s) → ⚫ Off (1s) → repeat
```

---

## 🚀 How to Run

1. Open `sketch_dec25a.ino` in Arduino IDE.
2. Install the required libraries via **Tools → Manage Libraries**:
   - `LiquidCrystal I2C` by Frank de Brabander
   - `Adafruit NeoPixel` by Adafruit
3. Select **ESP32S3 Dev Module** as the board.
4. Select the correct COM port and upload.
5. The LCD should light up immediately with the welcome message, and the LED will start cycling colors.

---

## 📝 Notes

- The NeoPixel brightness is set low (`25`) to avoid being too harsh on the eyes.
- The comment `// خاموش` means "Off" in Persian — this turns the LED off for 1 second at the end of each cycle.
- Make sure your I2C LCD address is `0x27` — some modules use `0x3F` instead. You can scan for it using an I2C scanner sketch if the screen doesn't turn on.
