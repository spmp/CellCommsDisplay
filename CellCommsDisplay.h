/**
 * Display functions for CellComms Adafruit_GFX displays
 *
 * Header contains:
 * - Average cell voltage
 * - Cell temperature maximum
 * - Cell with greatest voltage
 * - Cell with lowest voltage
 * - Number of cells balancing
 *
 * The bar chart has have a vertical bar for every cell showing current voltage,
 * and a horizonal line for the average voltage.
 * 
 * TODO:
 *  Remove hard coded bar widths for differing cell numbers.
 **/

#pragma once

#include "Arduino.h"
#include "CellComms.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <vector>

#define CELLCOMMSDISPLAY_BAR_START           8
#define CELLCOMMSDISPLAY_BAR_CELLWIDTH       4
#define CELLCOMMSDISPLAY_BAR_WIDTH           3

 class CellCommsDisplay
 {
  public:
    CellCommsDisplay(
      Adafruit_GFX & Display,
      CellComms & CellComms,
      float topBarProportion,
      uint16_t minMilliVolts,
      uint16_t maxMilliVolts
    );
    void displayBars(void);
    void displayHeader(void);
  private:
    Adafruit_GFX & _Display;
    CellComms & _CellComms;

    const float _TopBarProportion;
    const uint16_t _MinMilliVolts;
    const uint16_t _MaxMilliVolts;
    const uint16_t _HeaderHeight;
    const uint16_t _BarHeight;

    uint16_t millivoltsToHeight(uint16_t millivolts);
    void displayBar(uint8_t barNum, uint16_t millivolts);
 };
