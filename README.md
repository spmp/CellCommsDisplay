# CellCommsDisplay
Display class for Cell Top Module (CellComms) data on Adafruit_GFX display

## Minimal example
Instantiate the `CellComms` class as:
```
#include <Arduino.h>
#include <CellComms.h>
#include <CellCommsDisplay.h>
#include <Adafruit_SSD1306.h>

#define NUMBER_OF_CELLS                       12

#define CELLCOMMSDISPLAY_HEADER_PROPORTION    0.25
#define CELLCOMMSDISPLAY_MV_MAX               3700
#define CELLCOMMSDISPLAY_MV_MIN               2700

#define OLED_RESET                            4
// Instantiate serial device to talk to CTM ring:
HardwareSerial Serial1(1)

// Instantiate Cell Comms
CellComms cells(NUMBER_OF_CELLS, Serial1);

// Instantiate display
Adafruit_SSD1306 display(SSD1306_128_64_ID, OLED_RESET);

// Instantiate CellCommsDisplay
CellCommsDisplay ccDisplay(
  display,
  cells,
  CELLCOMMSDISPLAY_HEADER_PROPORTION,
  CELLCOMMSDISPLAY_MV_MIN,
  CELLCOMMSDISPLAY_MV_MAX
);

void setup()   {
  Serial1.begin(SERIAL1_BAUD, SERIAL_8N1, SERIAL1_RXPIN, SERIAL1_TXPIN);

  // Initialise Wire (I2C)
  Wire.begin(I2C_DISPLAY_SDA_PIN, I2C_DISPLAY_SCL_PIN, I2C_DISPLAY_FREQUENCY);
  delay(40);

  // Initilise display
  display.begin(SSD1306_SWITCHCAPVCC, ADAFRUIT_SSD1306_ADDRESS);

  display.clearDisplay();
  debugPrint("Setup Display");
  ...
}
```

In the program loop the display is updated as:
```
...

  cells.readCells();
  display.clearDisplay();
  ccDisplay.displayBars();
  ccDisplay.displayHeader();
```
