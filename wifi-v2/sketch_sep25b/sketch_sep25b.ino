#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

// =====================
// Wi-Fi Access Point
// =====================
const char* ssid = "ESP32-Network";
const char* password = "12345678";

WiFiServer server(80);

// =====================
// RGB NeoPixel
// =====================
#define LED_PIN 48
#define LED_COUNT 1

Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Track current color & state
uint32_t currentColor = 0x000000;
uint8_t currentBrightness = 40;

// =====================
// HTML / CSS / JS UI
// =====================
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>ESP32-S3 Light Hub</title>
  <style>
    :root {
      --bg: #0b0f19;
      --card-bg: rgba(22, 30, 49, 0.85);
      --border: rgba(255, 255, 255, 0.08);
      --text: #f1f5f9;
      --subtext: #94a3b8;
    }
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
      -webkit-tap-highlight-color: transparent;
    }
    body {
      background: radial-gradient(circle at 50% 10%, #1e293b, var(--bg));
      color: var(--text);
      min-height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      padding: 1.25rem;
    }
    .card {
      background: var(--card-bg);
      backdrop-filter: blur(12px);
      -webkit-backdrop-filter: blur(12px);
      border: 1px solid var(--border);
      border-radius: 1.5rem;
      padding: 1.75rem;
      width: 100%;
      max-width: 380px;
      box-shadow: 0 20px 40px rgba(0, 0, 0, 0.6);
      text-align: center;
    }
    .header-badge {
      display: inline-block;
      font-size: 0.7rem;
      font-weight: 700;
      letter-spacing: 0.08em;
      text-transform: uppercase;
      padding: 0.3rem 0.8rem;
      border-radius: 20px;
      background: rgba(56, 189, 248, 0.1);
      color: #38bdf8;
      border: 1px solid rgba(56, 189, 248, 0.2);
      margin-bottom: 0.75rem;
    }
    h1 {
      font-size: 1.4rem;
      font-weight: 700;
      margin-bottom: 0.25rem;
    }
    p {
      font-size: 0.825rem;
      color: var(--subtext);
      margin-bottom: 1.5rem;
    }
    /* Glow preview orb */
    .orb-wrapper {
      display: flex;
      justify-content: center;
      margin-bottom: 1.5rem;
    }
    .orb {
      width: 70px;
      height: 70px;
      border-radius: 50%;
      background: #1e293b;
      border: 3px solid rgba(255, 255, 255, 0.2);
      box-shadow: 0 0 20px rgba(0,0,0,0.5);
      transition: all 0.3s ease;
    }
    /* Grid of color presets */
    .color-grid {
      display: grid;
      grid-template-columns: repeat(5, 1fr);
      gap: 0.6rem;
      margin-bottom: 1.5rem;
    }
    .color-btn {
      width: 100%;
      aspect-ratio: 1;
      border-radius: 0.75rem;
      border: 2px solid transparent;
      cursor: pointer;
      transition: transform 0.15s ease, border-color 0.15s ease;
      box-shadow: 0 4px 10px rgba(0, 0, 0, 0.3);
    }
    .color-btn:active {
      transform: scale(0.9);
    }
    /* Controls Section */
    .control-group {
      background: rgba(15, 23, 42, 0.5);
      border: 1px solid var(--border);
      border-radius: 1rem;
      padding: 1rem;
      margin-bottom: 1.25rem;
    }
    .slider-header {
      display: flex;
      justify-content: space-between;
      font-size: 0.8rem;
      font-weight: 600;
      color: var(--subtext);
      margin-bottom: 0.5rem;
    }
    input[type=range] {
      width: 100%;
      accent-color: #38bdf8;
      cursor: pointer;
    }
    .actions {
      display: flex;
      gap: 0.75rem;
    }
    .custom-picker-btn {
      flex: 1;
      position: relative;
      background: #1e293b;
      border: 1px solid var(--border);
      color: var(--text);
      border-radius: 0.75rem;
      font-weight: 600;
      font-size: 0.85rem;
      display: flex;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      overflow: hidden;
      height: 44px;
    }
    .custom-picker-btn input[type=color] {
      position: absolute;
      opacity: 0;
      left: 0;
      top: 0;
      width: 100%;
      height: 100%;
      cursor: pointer;
    }
    .btn-off {
      flex: 1;
      height: 44px;
      border: none;
      border-radius: 0.75rem;
      background: #ef4444;
      color: white;
      font-weight: 600;
      font-size: 0.85rem;
      cursor: pointer;
      box-shadow: 0 4px 14px rgba(239, 68, 68, 0.3);
      transition: transform 0.15s ease;
    }
    .btn-off:active {
      transform: scale(0.95);
    }
  </style>
</head>
<body>
  <div class="card">
    <span class="header-badge">ESP32-S3 Wireless</span>
    <h1>RGB Studio</h1>
    <p>Select a color or choose your own</p>

    <!-- Visual Indicator -->
    <div class="orb-wrapper">
      <div id="orb" class="orb"></div>
    </div>

    <!-- 10 Preset Colors -->
    <div class="color-grid">
      <button class="color-btn" style="background: #ff1744;" onclick="sendHex('ff1744')"></button>
      <button class="color-btn" style="background: #ff6d00;" onclick="sendHex('ff6d00')"></button>
      <button class="color-btn" style="background: #ffd600;" onclick="sendHex('ffd600')"></button>
      <button class="color-btn" style="background: #00e676;" onclick="sendHex('00e676')"></button>
      <button class="color-btn" style="background: #00e5ff;" onclick="sendHex('00e5ff')"></button>
      <button class="color-btn" style="background: #2979ff;" onclick="sendHex('2979ff')"></button>
      <button class="color-btn" style="background: #651fff;" onclick="sendHex('651fff')"></button>
      <button class="color-btn" style="background: #f50057;" onclick="sendHex('f50057')"></button>
      <button class="color-btn" style="background: #ffe0b2;" onclick="sendHex('ffe0b2')"></button>
      <button class="color-btn" style="background: #ffffff;" onclick="sendHex('ffffff')"></button>
    </div>

    <!-- Brightness Slider -->
    <div class="control-group">
      <div class="slider-header">
        <span>BRIGHTNESS</span>
        <span id="bri-val">40%</span>
      </div>
      <input type="range" min="0" max="100" value="40" oninput="sendBri(this.value)">
    </div>

    <!-- Custom Wheel & Power -->
    <div class="actions">
      <label class="custom-picker-btn">
        <span>🎨 Custom Color</span>
        <input type="color" onchange="sendHex(this.value.substring(1))">
      </label>
      <button class="btn-off" onclick="sendOff()">Power OFF</button>
    </div>
  </div>

  <script>
    const orb = document.getElementById('orb');
    const briLabel = document.getElementById('bri-val');

    function updateOrb(colorHex, glow = true) {
      orb.style.background = '#' + colorHex;
      if (glow && colorHex !== '000000') {
        orb.style.boxShadow = '0 0 25px #' + colorHex + ', 0 0 10px #' + colorHex;
      } else {
        orb.style.boxShadow = 'none';
      }
    }

    function sendHex(hex) {
      updateOrb(hex, true);
      fetch('/set?hex=' + hex).catch(e => console.log(e));
    }

    function sendBri(val) {
      briLabel.innerText = val + '%';
      fetch('/bri?val=' + val).catch(e => console.log(e));
    }

    function sendOff() {
      updateOrb('0f172a', false);
      fetch('/off').catch(e => console.log(e));
    }
  </script>
</body>
</html>
)rawliteral";

// =====================
// Setup
// =====================
void setup() {
  Serial.begin(115200);

  led.begin();
  led.setBrightness(map(currentBrightness, 0, 100, 0, 255));
  led.clear();
  led.show();

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

// =====================
// Loop & API Routing
// =====================
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');

  // --- API ROUTE: Set Hex Color ---
  if (request.indexOf("GET /set?hex=") >= 0) {
    int idx = request.indexOf("GET /set?hex=") + 13;
    String hexStr = request.substring(idx, idx + 6);
    long rgb = strtol(hexStr.c_str(), NULL, 16);

    byte r = (rgb >> 16) & 0xFF;
    byte g = (rgb >> 8) & 0xFF;
    byte b = rgb & 0xFF;

    currentColor = led.Color(r, g, b);
    led.setPixelColor(0, currentColor);
    led.show();

    // Fast empty response
    client.println("HTTP/1.1 204 No Content\r\nConnection: close\r\n\r\n");
    client.stop();
    return;
  }

  // --- API ROUTE: Set Brightness ---
  if (request.indexOf("GET /bri?val=") >= 0) {
    int idx = request.indexOf("GET /bri?val=") + 13;
    int spaceIdx = request.indexOf(' ', idx);
    int percent = request.substring(idx, spaceIdx).toInt();

    currentBrightness = constrain(percent, 0, 100);
    led.setBrightness(map(currentBrightness, 0, 100, 0, 255));
    led.setPixelColor(0, currentColor);
    led.show();

    client.println("HTTP/1.1 204 No Content\r\nConnection: close\r\n\r\n");
    client.stop();
    return;
  }

  // --- API ROUTE: Turn Off ---
  if (request.indexOf("GET /off") >= 0) {
    currentColor = 0;
    led.clear();
    led.show();

    client.println("HTTP/1.1 204 No Content\r\nConnection: close\r\n\r\n");
    client.stop();
    return;
  }

  // --- DEFAULT ROUTE: Serve HTML Webpage ---
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.print(index_html);

  delay(5);
  client.stop();
}