/*
  Project-level TFT_eSPI User_Setup.h template.

  TFT_eSPI will pick up this file when present at lib/TFT_eSPI/User_Setup.h

  IMPORTANT:
  - You MUST change the driver define and pin assignments to match your
    exact display controller (ILI9488, ST7796, ILI9341, etc.) and wiring.
  - This is a conservative example and may not match your hardware.
*/

/*--------------------------------------------------------------------
 Example: common SPI parallel 480x320 display using ILI9488 (EXAMPLE ONLY)
 Uncomment the driver you need and set the pins below to match your wiring.
--------------------------------------------------------------------*/

//#define ILI9488_DRIVER  // <-- uncomment if your display uses ILI9488
//#define ST7796_DRIVER   // <-- uncomment if your display uses ST7796
//#define ILI9341_DRIVER  // <-- uncomment if your display uses ILI9341

// SPI pins (adjust to match your wiring)
#define TFT_MOSI  23
#define TFT_SCLK  18
#define TFT_CS    5  // Chip select control pin
#define TFT_DC    16 // Data Command control pin
#define TFT_RST   17 // Reset pin (could connect to -1 if unused)
#define TFT_BL    4  // Backlight control pin (optional)

// Touch pins (this project uses TOUCH_CS_PIN in code; keep consistent)
#define TOUCH_CS  14

// Display size
#define TFT_HEIGHT 320
#define TFT_WIDTH  480

// SPI frequency (adjust if you have reliability issues)
#define SPI_FREQUENCY  40000000  // 40MHz
#define SPI_READ_FREQUENCY  20000000

// If you need to use a parallel 8/16-bit bus instead of SPI, configure here.
// Most small SPI displays work fine with SPI settings above.

// -----------------------------------------------------------------
// If you don't want to edit the file, you can remove it and edit the
// TFT_eSPI library's User_Setup.h directly. Placing a copy here
// ensures the project uses the exact expected settings.
// -----------------------------------------------------------------

/* End of User_Setup.h */