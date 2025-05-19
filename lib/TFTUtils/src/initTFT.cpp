#include "TFTUtils.hpp"

void TFTUtils::initTFT() {
  tft.fillScreen(TFT_BLACK);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

