# ESP32S3 Sense MSP4021 TFT & Camera Demo

Demo for interfacing the MSP4021 4-inch TFT display (ST7796S, resistive touch XPT2046) and the XIAO ESP32S3 Sense With Camera (S3R8).

## Hardware Used

| Component                       | Details                                         |
|----------------------------------|------------------------------------------------|
| Display                         | MSP4021, 4.0", 480x320, ST7796S, SPI, XPT2046  |
| Microcontroller                  | XIAO ESP32S3 Sense With Camera S3R8            |
| Camera                           | OV2640/OV5640 (onboard)                        |
| Power                            | USB-C (5V)                                     |

## Wiring Plan

### TFT Display (ST7796S)

| MSP4021 Pin | ESP32S3 Pin | Signal           |
|-------------|-------------|------------------|
| VCC         | 3.3V        | Power            |
| GND         | GND         | Ground           |
| SCL (SCK)   | GPIO 9      | SPI Clock        |
| SDA (MOSI)  | GPIO 8      | SPI MOSI         |
| CS          | GPIO 10     | TFT Chip Select  |
| RESET       | GPIO 11     | TFT Reset        |
| DC/RS       | GPIO 12     | Data/Command     |
| LED         | 3.3V        | Backlight        |

### Touch Panel (XPT2046)

| Touch Pin   | ESP32S3 Pin | Signal              |
|-------------|-------------|---------------------|
| T_CS        | GPIO 14     | Touch Chip Select   |
| T_IRQ       | GPIO 7      | Touch IRQ           |
| T_DO (MISO) | GPIO 13     | SPI MISO            |
| T_DIN (MOSI)| GPIO 8      | SPI MOSI (shared)   |
| T_CLK       | GPIO 9      | SPI Clock (shared)  |

### Camera (OV2640/OV5640)
Prewired and handled via ESP32S3 Sense documentation.

### Diagram Example

```
MSP4021        XIAO ESP32S3 Sense S3R8
   VCC  ---->  3.3V
   GND  ---->  GND
   CS   ---->  GPIO 10
   RESET---->  GPIO 11
   DC/RS---->  GPIO 12
   SCL  ---->  GPIO 9
   SDA  ---->  GPIO 8
   LED  ---->  3.3V (or PWM)
Touch T_CS ->  GPIO 14
Touch T_IRQ->  GPIO 7
Touch DO  ->  GPIO 13
Touch DIN ->  GPIO 8
Touch CLK ->  GPIO 9
```

## Libraries Required

- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) (ST7796S support)
- [XPT2046_Touchscreen](https://github.com/PaulStoffregen/XPT2046_Touchscreen)
- [ESP32 Camera](https://github.com/espressif/esp32-camera)

## Setup

1. Wire components as shown.
2. Configure pin assignments in `User_Setup.h` for TFT_eSPI.
3. Install required libraries in PlatformIO or Arduino IDE.
4. Flash code to ESP32S3 Sense.

## Example Usage

- Demo draws moving box on TFT; touch panel works for input.
- Camera can stream image to display (see code).

## File Structure

```
/
├── README.md
├── src/
│   └── main.cpp
└── wiring_diagram.png   (add image if available)
```

## Credits

Designed for XIAO ESP32S3 Sense S3R8 & MSP4021 TFT.
