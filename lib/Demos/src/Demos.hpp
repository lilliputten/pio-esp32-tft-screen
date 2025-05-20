#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library, see configuration in `User_Setup.h`

#define TFT_GREY 0x5AEB  // New color

#define FONT_XS 1 // 26x10-12 (rows count depends on line height, see below, in range 12-10)
#define FONT_XS_SIZE 11
#define FONT_SM 2 // 20x8
#define FONT_SM_SIZE 16
#define FONT_MD 4 // 11x5
#define FONT_MD_SIZE 26
#define FONT_LG 6 // 6x3 3 lines per screen
#define FONT_LG_SIZE 40 // 3 lines per screen
#define FONT_LCD 7 // 5x2
#define FONT_LCD_SIZE 60
#define FONT_XL 8 // 3x1
#define FONT_XL_SIZE 80

// New background colour
// #define TFT_BROWN 0x38E0

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 1000

class Demos {

  public:
    void demoPrint(TFT_eSPI &tft);
    void demoFont(TFT_eSPI &tft);
    void demoEnv();

};
