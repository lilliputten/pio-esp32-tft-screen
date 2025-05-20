#include "Demos.hpp"

// @see https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Iteration count
long _count = 0;

void Demos::demoTempSensorInit() {
  // Start the DS18B20 sensor
  sensors.begin();
}

void Demos::demoTempSensorShow(TFT_eSPI &tft) {
  // Scan sensor data and print on both serial and tft screen...
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  Serial.print(temperatureC);
  Serial.println("ºC");

  int xp = 10;
  int yp = 10;
  int font1 = FONT_SM;
  int font2 = FONT_MD;
  int fh = tft.fontHeight(font1);
  int yp2 = yp + fh;

  // tft.fillScreen(TFT_BLACK);
  // tft.setTextFont(font1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(xp, yp, font1);

  long rand = random(0, 120);

  _count++;

  Serial.print("Loop: ");
  Serial.println(_count);
  Serial.print("Random: ");
  Serial.println(rand);

  tft.print("Loop: ");
  tft.print(_count);
  tft.print(" / ");
  tft.print(rand);
  tft.println("  -");

  tft.setCursor(xp, yp2, font2);

  tft.print(temperatureC, 1);
  tft.print("`C");
  tft.println("  -");
}
