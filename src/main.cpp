#include <Arduino.h>

#include "WiFi.h"

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library, see configuration in `User_Setup.h`

#include "Module.h"

Module module;

// put function declarations here:
int myFunction(int, int);
void initTFT();
void drawCircles1();
void initWiFi();
void scanWifi();

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

int count = 0;

void setup() {
  Serial.begin(115200);
  delay(100);

  initTFT();

  // Test module
  Serial.println("Module test...");
  // int testResult = moduleTest();
  int testResult = module.test();
  Serial.println("DEBUG: " + String(testResult));

  Serial.println("Setup done");
}

void loop() {
  // Serial.println("ILI9341_DRIVER: " + String(ILI9341_DRIVER));
  // Serial.println("ST7735_DRIVER: " + String(ST7735_DRIVER));

  Serial.println("TFT_WIDTH: " + String(TFT_WIDTH));
  Serial.println("TFT_HEIGHT: " + String(TFT_HEIGHT));

  Serial.println("TFT_DC: " + String(TFT_DC));
  Serial.println("TFT_RST: " + String(TFT_RST));
  Serial.println("TFT_CS: " + String(TFT_CS));

  Serial.println("Black");
  tft.fillScreen(TFT_BLACK);
  delay(1000);

  drawCircles1();

  count++;
  Serial.println("Count: " + String(count));
  scanWifi();

  Serial.println("White");
  tft.fillScreen(TFT_WHITE);
  delay(2000);
}

void initWiFi() {
  // Set WiFi to station mode and disconnect from an AP if it was previously
  // connected.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void initTFT() {
  tft.init();
  tft.setRotation(1);
  delay(100);
}

void drawCircles1() {
  tft.fillScreen(TFT_BLACK);

  // Draw some random filled ellipses
  for (int i = 0; i < 20; i++) {
    int rx = random(40);
    int ry = rx;  // random(40);
    int x = rx + random(160 - rx - rx);
    int y = ry + random(128 - ry - ry);
    tft.fillEllipse(x, y, rx, ry, random(0xFFFF));
  }
}

void scanWifi() {
  Serial.println("Scan start");

  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    Serial.println(
        "Nr | SSID                             | RSSI | CH | Encryption");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.printf("%2d", i + 1);
      Serial.print(" | ");
      Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
      Serial.print(" | ");
      Serial.printf("%4ld", WiFi.RSSI(i));
      Serial.print(" | ");
      Serial.printf("%2ld", WiFi.channel(i));
      Serial.print(" | ");
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:
          Serial.print("open");
          break;
        case WIFI_AUTH_WEP:
          Serial.print("WEP");
          break;
        case WIFI_AUTH_WPA_PSK:
          Serial.print("WPA");
          break;
        case WIFI_AUTH_WPA2_PSK:
          Serial.print("WPA2");
          break;
        case WIFI_AUTH_WPA_WPA2_PSK:
          Serial.print("WPA+WPA2");
          break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
          Serial.print("WPA2-EAP");
          break;
        case WIFI_AUTH_WPA3_PSK:
          Serial.print("WPA3");
          break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
          Serial.print("WPA2+WPA3");
          break;
        case WIFI_AUTH_WAPI_PSK:
          Serial.print("WAPI");
          break;
        default:
          Serial.print("unknown");
      }
      Serial.println();
      delay(10);
    }
  }
  Serial.println("");

  // Delete the scan result to free memory for code below.
  WiFi.scanDelete();
}
