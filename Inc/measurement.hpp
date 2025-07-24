#ifndef _MEASUREMENT_HPP_
#define _MEASUREMENT_HPP_

#include "app.hpp"
#include "const.h"
#include "drivers.hpp"
#include "state.h"
#include <math.h>

#define PI 3.14159265358979
#define MAX_COUNT 4095.0
#define MAX_ANALOG 3300.0
#define COUNT_TO_ANALOG(count) (count * MAX_ANALOG / MAX_COUNT)
#define ANALOG_TO_COUNT(analog) (analog * MAX_COUNT / MAX_ANALOG)
#define TARGET_ADC_VALUE 2048.0

class Mmt
{
public:
  static uint16_t pwmBuffer[MAX_BUFFER_SIZE];

  // current and voltage buffer
  static uint16_t *currentBuffer;
  static uint16_t *voltageBuffer;

  // Dual adc buffer
  static uint16_t adcBuffer[2 * MAX_BUFFER_SIZE];
  // Dual data buffer
  static int16_t dataBuffer[DATA_BUFFER_SIZE];

  // State control functions
  static void WAIT();
  static void DC();
  static void AC();
  static void MEASURE_DC();
  static void MEASURE_AC();
  static void SET_HPF();
  static void SET_VOFFSET();
  static void WHOAMI();
  static void CALIBRATE_CURRENT();

  // Setter functions (not state control)
  static void setAcEnable(float *params, int paramNum);
  static void setPWMWaveConfig(float *params, int paramNum);
  static void setPWMTimerConfig(float *params, int paramNum);
  static void setSWTimerConfig(float *params, int paramNum);
  static void setTimerConfig(float *params, int paramNum);
  static void setPWMLoad(float *params, int paramNum);
  static void setKpKi(float *params, int paramNum);

  // Getter functions (not state control)
  static void getUniqueId(uint32_t *uid);

  // Utils
  static void average(uint16_t *buffer, int len, uint16_t *result);
};

#endif