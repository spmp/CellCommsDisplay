/**
 * Display functions for CellComms using Adafruid GFX displays.
 * Currently tailored and tested on I2C 128x64 duo colour OLED display
 * Currently hard coded for my personal setup of 28 cells
 *
 * Style:
 *  As this library may be imported by a library manager and used by more
 *  than one device it is important that all initialisation values can be
 *  set at class instantiation AND NOT by altering preprocessor directives
 *
 * The class initialisation options are as follows:
 * - Display, the ADAFRUIT_GFX display device
 * - CellComms, the CellComms object containing the data to display
 * - topBarProportion, the proportion of the display used for the top bar
 * - minVoltage, the minimum voltage displayed
 * - maxVoltage, the maximum voltage displayed
 *
 * Header will contains:
 * - Average cell voltage
 * - Cell temperature maximum
 * - Cell with greatest voltage
 * - Cell with lowest voltage
 * - Num cells balancing
 *
 * The bar chart has a vertical bar for every cell, and a horizonal line
 * for the average.
 *
 * TODO
 * - Remove all project specific hard coded values
 * - Greater stats view
 * - Menu
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
