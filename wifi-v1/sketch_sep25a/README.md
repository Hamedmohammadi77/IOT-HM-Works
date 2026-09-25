# 📶 Exercise 2 — WiFi Access Point + Web LED Control (v1)

← [Back to Main](../../README.md)

---

## 📖 Description

This exercise turns the **ESP32-S3 into a WiFi Access Point** and hosts a simple **web server** on it. Any device that connects to the ESP32's network can open a browser and control the **NeoPixel RGB LED** by pressing buttons on a webpage — no router needed.

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
- Initializes the NeoPixel LED at brightness `25/255` and clears it
- Creates a WiFi Access Point with:
  - SSID: `ESP32-Network`
  - Password: `12345678`
- Starts a web server on port `80`
- Prints the AP IP address to Serial Monitor (usually `192.168.4.1`)

**Loop (repeats forever):**
- Waits for a client (browser) to connect
- Reads the incoming HTTP GET request
- Checks the URL path and reacts:

| URL path | Action |
|----------|--------|
| `/red` | 🔴 Sets LED to Red |
| `/green` | 🟡 Sets LED to Yellow (bug — see Notes) |
| `/off` | ⚫ Turns LED off |

- Sends back an HTML page with three buttons: **RED ON**, **OFF**, **green on**
- Disconnects the client after responding

---

## 🌐 How to Connect

1. Upload the sketch to your ESP32-S3.
2. Open **Serial Monitor** at `115200` baud — you'll see the IP address printed.
3. On your phone or laptop, connect to WiFi network **`ESP32-Network`** (password: `12345678`).
4. Open a browser and go to **`192.168.4.1`**.
5. Use the buttons to control the LED.

---

## 🚀 How to Run

1. Open `sketch_sep25a.ino` in Arduino IDE.
2. Install the required library via **Tools → Manage Libraries**:
   - `Adafruit NeoPixel` by Adafruit
3. Select **ESP32S3 Dev Module** as the board.
4. Select the correct COM port and upload.

---

## 📝 Notes

- There is a small bug in the `/green` handler — the color is set to `(255, 255, 0)` which is **Yellow**, not Green. Green would be `(0, 255, 0)`. This is fixed in **v2**.
- The comment `// دریافت HTTP Request` means "Receive HTTP Request" in Persian.
- This version handles **one client at a time** — the next client waits until the current one disconnects.
- This is a stepping stone toward v2, which improves on this foundation.
