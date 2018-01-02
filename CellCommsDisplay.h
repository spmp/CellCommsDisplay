/**
 * Display functions for CellComms on I2C 128x64 display using AdaFruit driver
 * Currently hard coded for my personal setup of 28 cells
 *
 * This will some major functional components
 * - A class insantiated with display device
 * - Function to display header (yellow on my display)
 * - Function to display per cell bar graph and average
 * - Future: Menu for interaction
 *
 * Header will contain as much information as possible, hopefully at least:
 * - Average cell voltage
 * - Num cells balancing
 * - Cell temperature maximum
 * - Cell with greatest voltage
 * - Cell with lowest voltage
 *
 * The bar chart will have a vertical bar for every cell, and a horizonal line
 * for the average.
 **/

#pragma once

#include "Arduino.h"
#include "CellComms.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// #include <Fonts/FreeMonoBold18pt7b.h>
// #include <Fonts/FreeMonoOblique9pt7b.h>
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
