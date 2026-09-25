# 📡 Exercise 3 — WiFi Access Point + RGB Studio Web UI (v2)

← [Back to Main](../../README.md)

---

## 📖 Description

This is a major upgrade over v1. The ESP32-S3 still acts as a **WiFi Access Point**, but now serves a fully designed **"RGB Studio" web app** with a modern dark UI. Instead of plain HTML buttons, the user gets a **color grid**, a **brightness slider**, a **custom color picker**, and a **live glow orb** that previews the current color — all controlled over WiFi with no router needed.

The communication is also improved: the browser sends lightweight API requests (`/set`, `/bri`, `/off`) using `fetch()` instead of reloading the whole page each time.

---

## 🛠️ Hardware Required

| Component | Details |
|-----------|---------|
| Board | ESP32-S3 |
| RGB LED | NeoPixel (pin `48`, 1 LED) |
| Connection | WiFi (Access Point mode — no router needed) |

---

## 📚 Libraries Used

| Library | Purpose |
|---------|---------|
| `WiFi.h` | WiFi and web server |
| `Adafruit_NeoPixel` | RGB LED control |

---

## 📋 How It Works

**Setup (runs once):**
- Initializes the NeoPixel LED at brightness `40/100` (mapped to `0–255`)
- Creates a WiFi Access Point:
  - SSID: `ESP32-Network`
  - Password: `12345678`
- Starts a web server on port `80`
- Prints the IP address to Serial Monitor (usually `192.168.4.1`)

**Loop — API Routing:**

The server handles 4 routes:

| Route | Method | Action |
|-------|--------|--------|
| `/set?hex=RRGGBB` | GET | Parses hex color → sets LED color |
| `/bri?val=0–100` | GET | Maps percentage → brightness (0–255) |
| `/off` | GET | Clears LED, resets `currentColor` to `0` |
| `/` (default) | GET | Serves the full HTML web app |

API routes respond with `HTTP 204 No Content` (empty, fast) so the browser doesn't reload. Only the root `/` sends back the full HTML page.

**Web UI Features:**
- 🔴 **10 preset color buttons** in a 5-column grid
- 🌟 **Live orb preview** — glows with the selected color
- 🔆 **Brightness slider** (0–100%) with real-time label update
- 🎨 **Custom color picker** — full color wheel via native browser input
- ⚫ **Power OFF button** — turns off the LED and dims the orb

---

## 🆚 What Changed from v1

| Feature | v1 | v2 |
|---------|----|----|
| UI | Plain HTML buttons | Styled dark glassmorphism card |
| Colors | 3 fixed options (red, yellow, off) | 10 presets + full custom color wheel |
| Brightness | Fixed | Adjustable slider (0–100%) |
| Communication | Full page reload per click | `fetch()` API — no reload |
| Color format | Hardcoded RGB values | Hex string parsed on the ESP32 |
| Green bug from v1 | `(255, 255, 0)` = Yellow ❌ | Fixed — proper hex parsing ✅ |

---

## 🌐 How to Connect

1. Upload the sketch to your ESP32-S3.
2. Open **Serial Monitor** at `115200` baud to see the IP address.
3. On your phone or laptop, connect to WiFi **`ESP32-Network`** (password: `12345678`).
4. Open a browser and go to **`192.168.4.1`**.
5. Use the web UI to control the LED.

---

## 🚀 How to Run

1. Open `sketch_sep25b.ino` in Arduino IDE.
2. Install the required library via **Tools → Manage Libraries**:
   - `Adafruit NeoPixel` by Adafruit
3. Select **ESP32S3 Dev Module** as the board.
4. Select the correct COM port and upload.

---

## 📝 Notes

- The HTML is stored in flash memory using `PROGMEM` and a raw string literal (`R"rawliteral(...)"`) — this avoids using RAM for the large UI string.
- `currentColor` is tracked in memory so brightness changes re-apply the last color correctly.
- The `strtol()` function parses the hex color string sent from the browser directly into R, G, B bytes on the ESP32.
- `constrain()` and `map()` ensure brightness values always stay in valid ranges.
