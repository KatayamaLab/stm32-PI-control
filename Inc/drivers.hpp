#ifndef _DRIVERS_HPP_
#define _DRIVERS_HPP_

#ifdef USE_HAL_DRIVER
#include "stm32f3xx_hal.h"
#endif

#ifdef __cplusplus

#include "app.hpp"
#include "const.h"
#include "main.h"
#include "state.h"
#include <cstring>

class Drivers
{

public:
  // UART
  static void uartPutString(const char *);
  static void uartPutChar(char);
  static void uartProcessChar(char);
  // Timer
  static void updateTimer3Config(const uint16_t psc, const uint16_t arr);
  static void updateTimer6Config(const int psc, const int arr);
  static void updateTimer16Config(const uint16_t psc, const uint16_t arr);

  // PWM
  static void GPIO_PWMLOAD(const bool);

  // ADC
  // DMA measurement
  static void selectADC1Channel(const int channel);
  static void selectADC1MultiMode(const bool multi);
  static void selectADC1DMATransferSize(const bool isWord);
  static void getADC1_1_DMA(uint16_t *value, int len);
  static void getADC1_2_DMA(uint16_t *value, int len);
  static void getADC_Dual(uint16_t *value, int len);

  // DAC
  // AC signal out
  static void setDAC1_1(uint16_t *buffer, int len);
  // DC offset out
  static void setDAC1_2(const uint16_t value);

  // GPIO
  static void GPIO_IAC(const bool state);
  static void GPIO_VAC(const bool state);
  static void GPIO_IDENT(const bool state);

  // Utils
  static void getUniqueId(uint32_t *uid);
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif

  void uartIRQHandler(uint8_t *buf);
  void tim3IRQHandler();
#ifdef __cplusplus
}
#endif

#endif