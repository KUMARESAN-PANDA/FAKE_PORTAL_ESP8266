# ESP8266 Captive Portal with OLED Display

This project creates a simple captive portal on an ESP8266 microcontroller, providing a login page when users connect to a Wi-Fi access point named "PublicWiFi." The ESP8266 also uses an OLED display to show relevant information, such as the IP address of the access point.

## Features
- Creates an open Wi-Fi access point named **"PublicWiFi"**.
- Provides a captive portal with a login page.
- Displays the network status and IP address on an OLED screen.
- Uses DNS spoofing to redirect any request to the captive portal page.

## Components
- **ESP8266 Module**: Handles Wi-Fi and web server functionalities.
- **Adafruit SSD1306 OLED Display**: Displays network status and IP address.
- **DNS Server**: Redirects DNS requests to the ESP8266 captive portal page.
- **ESP8266WebServer Library**: Hosts the login page and handles form submission.

## Hardware Requirements
- ESP8266 module (e.g., NodeMCU or Wemos D1 Mini)
- Adafruit SSD1306 OLED display (128x64 resolution)
- Connecting wires for the OLED display (I2C interface)

## Software Requirements
- Arduino IDE with ESP8266 support
- Required libraries:
  - **ESP8266WiFi.h**: For Wi-Fi management.
  - **ESP8266WebServer.h**: To create a simple web server.
  - **DNSServer.h**: For DNS redirection.
  - **Adafruit_GFX.h** and **Adafruit_SSD1306.h**: For OLED display handling.

## Circuit Diagram
1. Connect the OLED display to the ESP8266 using I2C (SDA to D2, SCL to D1).
2. Power the ESP8266 and OLED from a suitable power source (USB or 3.3V).

## Code Explanation

### Libraries and Constants
```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
