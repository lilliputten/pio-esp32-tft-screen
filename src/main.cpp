#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library, see configuration in `User_Setup.h`
#include <WiFi.h>

#include "Module.hpp"

#define TFT_GREY 0x5AEB  // New color

// New background colour
// #define TFT_BROWN 0x38E0

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 500

Module module;

void demoEnv();
void initTFT();
void drawCircles1();
void initWiFi();
void scanWifi();
void demoModule();
void demoPrint();
void demoFont();

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

int count = 0;

void setup() {
  Serial.begin(115200);

  initTFT();
  // demoEnv();
  // demoModule();

  Serial.println("Setup done");
}

void loop() {
  demoPrint();
  // demoFont();

  // Serial.println("Black");
  // tft.fillScreen(TFT_BLACK);
  // delay(1000);
  //
  // drawCircles1();
  //
  // // count++;
  // // Serial.println("Count: " + String(count));
  //
  // scanWifi();
  //
  // Serial.println("White");
  // tft.fillScreen(TFT_WHITE);
  // delay(2000);
}

// Custom functions...

void demoFont() {
  unsigned long targetTime = millis();

  // First we test them with a background colour set
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
  tft.drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
  tft.drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
  tft.drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);
  int xpos = 0;
  xpos += tft.drawString("xyz{|}~", 0, 64, 2);
  tft.drawChar(127, xpos, 64, 2);
  delay(WAIT);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.drawString(" !\"#$%&'()*+,-.", 0, 0, 4);
  tft.drawString("/0123456789:;", 0, 26, 4);
  tft.drawString("<=>?@ABCDE", 0, 52, 4);
  tft.drawString("FGHIJKLMNO", 0, 78, 4);
  tft.drawString("PQRSTUVWX", 0, 104, 4);
  delay(WAIT);

  tft.fillScreen(TFT_BLACK);
  tft.drawString("YZ[\\]^_`abc", 0, 0, 4);
  tft.drawString("defghijklmno", 0, 26, 4);
  tft.drawString("pqrstuvwxyz", 0, 52, 4);
  xpos = 0;
  xpos += tft.drawString("{|}~", 0, 78, 4);
  tft.drawChar(127, xpos, 78, 4);
  delay(WAIT);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);

  tft.drawString("012345", 0, 0, 6);
  tft.drawString("6789", 0, 40, 6);
  tft.drawString("apm-:.", 0, 80, 6);
  delay(WAIT);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_RED, TFT_BLACK);

  tft.drawString("0123", 0, 0, 7);
  tft.drawString("4567", 0, 60, 7);
  delay(WAIT);

  tft.fillScreen(TFT_BLACK);
  tft.drawString("890:.", 0, 0, 7);
  tft.drawString("", 0, 60, 7);
  delay(WAIT);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);

  tft.drawString("01", 0, 0, 8);
  delay(WAIT);

  tft.drawString("23", 0, 0, 8);
  delay(WAIT);

  tft.drawString("45", 0, 0, 8);
  delay(WAIT);

  tft.drawString("67", 0, 0, 8);
  delay(WAIT);

  tft.drawString("89", 0, 0, 8);
  delay(WAIT);

  tft.drawString("0:.", 0, 0, 8);
  delay(WAIT);

  tft.setTextColor(TFT_MAGENTA);
  tft.drawNumber(millis() - targetTime, 0, 100, 4);
  delay(4000);

  // Now test them with transparent background
  targetTime = millis();

  tft.setTextSize(1);
  tft.fillScreen(TFT_BROWN);
  tft.setTextColor(TFT_GREEN);

  tft.drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
  tft.drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
  tft.drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
  tft.drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);
  xpos = 0;
  xpos += tft.drawString("xyz{|}~", 0, 64, 2);
  tft.drawChar(127, xpos, 64, 2);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.setTextColor(TFT_GREEN);

  tft.drawString(" !\"#$%&'()*+,-.", 0, 0, 4);
  tft.drawString("/0123456789:;", 0, 26, 4);
  tft.drawString("<=>?@ABCDE", 0, 52, 4);
  tft.drawString("FGHIJKLMNO", 0, 78, 4);
  tft.drawString("PQRSTUVWX", 0, 104, 4);

  delay(WAIT);
  tft.fillScreen(TFT_BROWN);
  tft.drawString("YZ[\\]^_`abc", 0, 0, 4);
  tft.drawString("defghijklmno", 0, 26, 4);
  tft.drawString("pqrstuvwxyz", 0, 52, 4);
  xpos = 0;
  xpos += tft.drawString("{|}~", 0, 78, 4);
  tft.drawChar(127, xpos, 78, 4);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.setTextColor(TFT_BLUE);

  tft.drawString("012345", 0, 0, 6);
  tft.drawString("6789", 0, 40, 6);
  tft.drawString("apm-:.", 0, 80, 6);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.setTextColor(TFT_RED);

  tft.drawString("0123", 0, 0, 7);
  tft.drawString("4567", 0, 60, 7);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.drawString("890:.", 0, 0, 7);
  tft.drawString("", 0, 60, 7);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.setTextColor(TFT_YELLOW);

  tft.drawString("0123", 0, 0, 8);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.drawString("4567", 0, 0, 8);
  delay(WAIT);

  tft.fillScreen(TFT_BROWN);
  tft.drawString("890:.", 0, 0, 8);
  delay(WAIT);

  tft.setTextColor(TFT_MAGENTA);

  tft.drawNumber(millis() - targetTime, 0, 100, 4);
  delay(4000);;
}

void demoPrint() {
  Serial.println("demoPrint");

  // Fill screen with grey so we can see the effect of printing with and without
  // a background colour defined
  tft.fillScreen(TFT_GREY);

  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with
  // 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size
  // multiplier to 1
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  // We can now plot text on screen using the "print" class
  tft.println("Hello World!");

  // Set the font colour to be yellow with no background, set to font 7
  tft.setTextColor(TFT_YELLOW);
  tft.setTextFont(2);
  tft.println(1234.56);

  // Set the font colour to be red with black background, set to font 4
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setTextFont(4);
  tft.println((long)3735928559, HEX);  // Should print DEADBEEF

  // Set the font colour to be green with black background, set to font 2
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(2);
  tft.println("Groop");

  // Test some print formatting functions
  float fnumber = 123.45;
  // Set the font colour to be blue with no background, set to font 2
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(2);
  tft.print("Float = ");
  tft.println(fnumber);  // Print floating point number
  tft.print("Binary = ");
  tft.println((int)fnumber, BIN);  // Print as integer value in binary
  tft.print("Hexadecimal = ");
  tft.println((int)fnumber, HEX);  // Print as integer number in Hexadecimal

  // while(1) yield(); // We must yield() to stop a watchdog timeout.

  delay(5000);
}

void demoEnv() {
  // Test project parameters...
  Serial.println("TFT_WIDTH: " + String(TFT_WIDTH));
  Serial.println("TFT_HEIGHT: " + String(TFT_HEIGHT));

  Serial.println("TFT_DC: " + String(TFT_DC));
  Serial.println("TFT_RST: " + String(TFT_RST));
  Serial.println("TFT_CS: " + String(TFT_CS));
}

void demoModule() {
  // Test module
  Serial.println("Module test...");
  // int demoResult = moduleTest();
  int demoResult = module.test();
  Serial.println("DEBUG: " + String(demoResult));
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
      Serial.printf("%4ld", (long)WiFi.RSSI(i));
      Serial.print(" | ");
      Serial.printf("%2ld", (long)WiFi.channel(i));
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
