#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library, see configuration in `User_Setup.h`

class TFTUtils {

 public:
  TFT_eSPI tft = TFT_eSPI();

  TFT_eSPI& getTFT();
  void initTFT();

  TFTUtils() {
    // Constructor
    Serial.println("TFTUtils constructor");
    initTFT();
  }
};
