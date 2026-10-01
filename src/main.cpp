#include "Demos.hpp"
#include "TFTUtils.hpp"
// #include "WiFiUtils.hpp"

TFTUtils tftUtils;
Demos demos;
// WiFiUtils wiFiUtils;

// Iteration count
long count = 0;

void setup() {
  Serial.begin(115200);

  delay(100);

  tftUtils.initTFT();

  // wiFiUtils.initWiFi();
  // wiFiUtils.scanWifi();

  demos.demoTempSensorInit();

  Serial.println("Setup done");
}

void loop() {
  count++;
  Serial.println("Loop count: " + String(count));

  demos.demoTempSensorShow(tftUtils.tft);

  // // demos.demoPrint(tftUtils.tft);
  // demos.demoFont(tftUtils.tft);

  // while(1) yield(); // We must yield() to stop a watchdog timeout.
  delay(5000);
}
