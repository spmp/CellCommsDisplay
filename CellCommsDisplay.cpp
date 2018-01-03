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

#include "CellCommsDisplay.h"
#include "Arduino.h"

CellCommsDisplay::CellCommsDisplay (
  Adafruit_GFX & Display,
  CellComms & CellComms,
  float topBarProportion,
  uint16_t minMilliVolts,
  uint16_t maxMilliVolts
) : _Display (Display), _CellComms (CellComms),
    _TopBarProportion (topBarProportion),
    _MinMilliVolts (minMilliVolts), _MaxMilliVolts (maxMilliVolts),
    _HeaderHeight (_Display.height() * _TopBarProportion),
    _BarHeight (_Display.height() - _HeaderHeight)
{
}

uint16_t CellCommsDisplay::millivoltsToHeight(uint16_t millivolts) {
  // Convert float to uint16_t
  if (millivolts >= _MinMilliVolts) {
    return (uint16_t) (
      // Millivolts subtracting
      (millivolts - _MinMilliVolts) *
      1.0 * _BarHeight /
      (_MaxMilliVolts - _MinMilliVolts)
    );
  } else {
    return 0;
  }
}

void CellCommsDisplay::displayBar(uint8_t barNum, uint16_t millivolts) {
  uint16_t height =
    // Choose minimum of calculated height or maximum blue height
    std::min(
      millivoltsToHeight(millivolts),
      (uint16_t) _BarHeight
  );
  uint16_t x = CELLCOMMSDISPLAY_BAR_START + barNum * CELLCOMMSDISPLAY_BAR_CELLWIDTH;
  uint16_t y = _Display.height() - height;
  _Display.fillRect(x, y, CELLCOMMSDISPLAY_BAR_WIDTH, height, WHITE);
}

void CellCommsDisplay::displayBars(void) {

  // Draw bars, one bar at a time
  for (uint8_t i = 0; i < _CellComms.cellDataVect.size(); i++) {
    displayBar(i, _CellComms.cellDataVect[i].millivolts);
  }
  // Draw average line
  _Display.drawFastHLine(
    // x
    CELLCOMMSDISPLAY_BAR_START,
    // y
    _Display.height() - millivoltsToHeight(_CellComms.millivoltsMean()),
    // length
    _Display.width() - CELLCOMMSDISPLAY_BAR_START,
    // colour
    WHITE
  );
}

void CellCommsDisplay::displayHeader(void) {
  float meanVoltage = _CellComms.millivoltsMean() * 0.001;
  float maxTemperature = _CellComms.temperatureMax() * 0.1;
  String headerLine =
    // mean voltage to three decimal places
    // String(" t ") +
    String(meanVoltage, 3)  +
    // Max temperature to on decimal place
    String(" t") + String(maxTemperature, 0) +
    // Minimum and maximum cell number
    String(" +") + String(_CellComms.millivoltsMaxCell()) +
    String(" -") + String(_CellComms.millivoltsMinCell()) +
    // Number of balancing cells
    String(" ")   + String(_CellComms.balancingNum());

    // Display the text
    _Display.setTextSize(1);
    _Display.setTextColor(WHITE);
    // TODO make these positions dynamic! Where does the 6 come from!
    _Display.setCursor(0,6);
    // Print the line to the display
    _Display.print(headerLine);
}
