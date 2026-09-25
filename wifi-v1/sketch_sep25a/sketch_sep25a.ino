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

Adafruit_NeoPixel led(
  LED_COUNT,
  LED_PIN,
  NEO_GRB + NEO_KHZ800);

// =====================
// Setup
// =====================

void setup() {

  Serial.begin(115200);

  // =====================
  // LED
  // =====================

  led.begin();
  led.setBrightness(25);
  led.clear();
  led.show();

  // =====================
  // Access Point
  // =====================

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Access Point started!");

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // =====================
  // Web Server
  // =====================

  server.begin();
}

// =====================
// Loop
// =====================

void loop() {

  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  Serial.println("Client connected!");

  // دریافت HTTP Request
  String request = client.readStringUntil('\r');

  Serial.println(request);

  // =====================
  // RED
  // =====================

  if (request.indexOf("GET /red") >= 0) {

    led.setPixelColor(
      0,
      led.Color(255, 0, 0));

    led.show();
  }

  if (request.indexOf("GET /green") >= 0) {

    led.setPixelColor(
      0,
      led.Color(255, 255, 0));

    led.show();
  }

  // =====================
  // OFF
  // =====================

  if (request.indexOf("GET /off") >= 0) {

    led.clear();
    led.show();
  }

  // =====================
  // Send HTML
  // =====================

  //send that we will send you a web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<title>ESP32</title>");
  client.println("</head>");

  client.println("<body>");

  client.println("<h1>ESP32-S3 Control</h1>");

  client.println("<a href='/red'>");
  client.println("<button>RED ON</button>");
  client.println("</a>");

  client.println("<br><br>");

  client.println("<a href='/off'>");
  client.println("<button>OFF</button>");
  client.println("</a>");

  client.println("<br><br>");

  client.println("<a href='/green'>");
  client.println("<button>green on</button>");
  client.println("</a>");

  client.println("</body>");
  client.println("</html>");

  delay(10);

  client.stop();

  Serial.println("Client disconnected.");
}