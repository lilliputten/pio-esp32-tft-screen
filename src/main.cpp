#include "Demos.hpp"
#include "TFTUtils.hpp"
// #include "WiFiUtils.hpp"

TFTUtils tftUtils;
// WiFiUtils wiFiUtils;
Demos demos;

// Iteration count
long count = 0;

void setup() {
  Serial.begin(115200);

  delay(100);

  tftUtils.initTFT();

  // wiFiUtils.initWiFi();
  // wiFiUtils.scanWifi();

  Serial.println("Setup done");
}

void loop() {
  count++;
  Serial.println("Loop count: " + String(count));

  // demos.demoPrint(tftUtils.tft);
  demos.demoFont(tftUtils.tft);

  // while(1) yield(); // We must yield() to stop a watchdog timeout.
  delay(1000);
}
