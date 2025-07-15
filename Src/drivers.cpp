#include "drivers.hpp"

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;

extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac2;
extern DMA_HandleTypeDef hdma_dac1_ch1;
extern DMA_HandleTypeDef hdma_dac2_ch1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim16;

// global state
State state;

// UART
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

  // When UART error occurs

  uint32_t error = HAL_UART_GetError(huart);

  switch (error)
  {
  case HAL_UART_ERROR_NONE:
    break;

  case HAL_UART_ERROR_ORE:
    // Overrun error

    // Recover
    SET_BIT(huart->Instance->ICR, USART_ICR_PECF);
    SET_BIT(huart->Instance->RQR, USART_RQR_RXFRQ);
    SET_BIT(huart->Instance->CR1, USART_CR1_RXNEIE);
    break;

  default:
    STATE_setError(&state, UART_UNHANDLED_FAILURE);
  }
}

void uartIRQHandler(uint8_t *buf)
{
  Drivers::uartProcessChar(*buf);
  // echo back
  if (STATE_getEchoBack(&state))
  {
    Drivers::uartPutChar(*buf);
  }
}

void Drivers::uartPutString(const char *buf)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)buf, strlen(buf), 100);
}

void Drivers::uartPutChar(char ch)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 100);
}

void Drivers::uartProcessChar(char ch)
{
  // Add to input buffer
  // return true if end of line
  // 前のコマンドが処理されるまで入力を受け付けない
  if (!STATE_getCmdAvailable(&state) && CLI::getLine(ch))
  {
    STATE_setCmdAvailable(&state);
  }
}

// Timer
void Drivers::updateTimer16Config(const uint16_t swpsc, const uint16_t swarr)
{
  __HAL_TIM_SET_PRESCALER(&htim16, swpsc - 1);
  __HAL_TIM_SET_AUTORELOAD(&htim16, swarr - 1);
}

void Drivers::updateTimer6Config(const int psc, const int arr)
{
  if (HAL_ADC_Stop(&hadc1) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  if (HAL_ADC_Stop(&hadc2) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }
  // Set timer settings
  // Input data range is garanteed by caller

  __HAL_TIM_SET_PRESCALER(&htim6, psc - 1);
  __HAL_TIM_SET_AUTORELOAD(&htim6, arr - 1);

}

// PWM
void Drivers::GPIO_PWMLOAD(const bool flag)
{
  if (flag)
  {
    STATE_resetPWMIdx(&state);

    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim3);
  }
  else
  {
    HAL_TIM_Base_Stop(&htim3);
    HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1);
  }
}

void Drivers::updateTimer3Config(const uint16_t psc, const uint16_t arr)
{
  __HAL_TIM_SET_PRESCALER(&htim3, psc - 1);
  __HAL_TIM_SET_AUTORELOAD(&htim3, arr - 1);
}

void tim3IRQHandler()
{

  // パルス幅
  uint16_t *pulseWidth = STATE_getPWMBuff(&state);

  // 現在のパルス幅のインデックス
  int idx = STATE_getPWMIdx(&state);

  if (idx == 0)
  {
    HAL_GPIO_WritePin(SIN_FLAG_GPIO_Port, SIN_FLAG_Pin, GPIO_PIN_RESET);
  }

  if (STATE_isPWMLastIndex(&state))
  {
    HAL_GPIO_WritePin(SIN_FLAG_GPIO_Port, SIN_FLAG_Pin, GPIO_PIN_SET);
  }

  // パルス幅を設定
  __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, (uint32_t)pulseWidth[idx]);

  // インデックスをインクリメント
  STATE_incrementPWMIdx(&state);
}

// ADC

// ADC non-blocking callbacks
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  // When conversion complete

  // Stop ADC
  if (HAL_ADC_Stop(hadc) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  STATE_setInternalState(&state, ANALYZER_INTERNAL_COMPLETE);
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  uint32_t error = HAL_ADC_GetError(hadc);

  STATE_setInternalState(&state, ANALYZER_INTERNAL_READY);

  switch (error)
  {
  case HAL_ADC_ERROR_INTERNAL:
    // ADC IP internal error
    STATE_setError(&state, ADC_INTERNAL_FAILURE);
    break;
  case HAL_ADC_ERROR_OVR:
    // Overrun err to recover (Set ADSTP/JADSTP)
    SET_BIT(hadc1.Instance->CR, ADC_CR_ADSTP);
    SET_BIT(hadc1.Instance->CR, ADC_CR_JADSTP);
    STATE_setError(&state, ADC_OVERRUN_FAILURE);
    break;
  case HAL_ADC_ERROR_DMA:
    // DMA transfer error
    STATE_setError(&state, ADC_DMA_TRANSFER_FAILURE);
    break;
  default:
    // Invalid callback error
    STATE_setError(&state, UNKNOWN_ERROR);
    break;
  }

  if (HAL_ADC_Stop(hadc) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }
}

void Drivers::selectADC1Channel(const int channel)
{

  // Check current channel
  int nowCh = (int)(hadc1.Instance->SQR1 & ADC_SQR1_SQ1) >> ADC_SQR1_SQ1_Pos;
  if (nowCh == channel)
  {
    return;
  }

  // New channel setting
  ADC_ChannelConfTypeDef channelConfig;
  channelConfig.Channel = channel;
  channelConfig.Rank = 1;
  channelConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;

  if (HAL_ADC_ConfigChannel(&hadc1, &channelConfig) != HAL_OK)
  {
    STATE_setError(&state, ADC_CHANNEL_SET_FAILURE);
    return;
  }
}

void Drivers::selectADC1MultiMode(const bool isMulti)
{

  // Set mode
  ADC_MultiModeTypeDef multimode = {0};

  multimode.Mode = isMulti ? ADC_DUALMODE_REGSIMULT : ADC_MODE_INDEPENDENT;
  multimode.DMAAccessMode = ADC_DMAACCESSMODE_12_10_BITS;
  multimode.TwoSamplingDelay = ADC_TWOSAMPLINGDELAY_1CYCLE;

  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    STATE_setError(&state, ADC_MULTIMODE_SET_FAILURE);
    return;
  }
}

void Drivers::selectADC1DMATransferSize(const bool isWord)
{

  // Clear enable
  hdma_adc1.Instance->CCR &= ~DMA_CCR_EN;

  // Change DMA transfer memory size
  hdma_adc1.Instance->CCR &= ~DMA_CCR_MSIZE;
  hdma_adc1.Instance->CCR |= isWord ? DMA_CCR_MSIZE_1 : DMA_CCR_MSIZE_0;
}

void Drivers::getADC1_1_DMA(uint16_t *value, int len)
{

  // To configure settings, ADC must be stopped
  if (HAL_ADC_Stop(&hadc1) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  if (HAL_ADC_Stop(&hadc2) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  // Select channel
  Drivers::selectADC1Channel(ADC_CHANNEL_1);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Select multi mode
  Drivers::selectADC1MultiMode(false);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Change DMA transfer memory size
  Drivers::selectADC1DMATransferSize(false);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Start ADC
  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)value, len) != HAL_OK)
  {
    STATE_setError(&state, ADC_START_FAILURE);
    return;
  }

  STATE_setInternalState(&state, ANALYZER_INTERNAL_BUSY);
}

void Drivers::getADC1_2_DMA(uint16_t *value, int len)
{
  // To configure settings, ADC must be stopped
  if (HAL_ADC_Stop(&hadc1) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  // Select channel
  Drivers::selectADC1Channel(ADC_CHANNEL_2);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Start ADC
  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)value, len) != HAL_OK)
  {
    STATE_setError(&state, ADC_START_FAILURE);
    return;
  }

  STATE_setInternalState(&state, ANALYZER_INTERNAL_BUSY);
}

void Drivers::getADC_Dual(uint16_t *value, int len)
{

  if (HAL_ADC_Stop(&hadc1) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  if (HAL_ADC_Stop(&hadc2) != HAL_OK)
  {
    STATE_setError(&state, ADC_STOP_FAILURE);
    return;
  }

  // Select channel
  Drivers::selectADC1Channel(ADC_CHANNEL_4);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Select multi mode
  Drivers::selectADC1MultiMode(true);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Change DMA transfer memory size
  Drivers::selectADC1DMATransferSize(true);
  if (STATE_hasError(&state))
  {
    return;
  }

  // Start ADC multi mode
  if (HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)value, len) != HAL_OK)
  {
    STATE_setError(&state, ADC_START_FAILURE);
    return;
  }

  STATE_setInternalState(&state, ANALYZER_INTERNAL_BUSY);
}

// DAC
void Drivers::setDAC1_1(uint16_t *buffer, int len)
{

  // if dma already running, stop dac
  if (HAL_DMA_GetState(&hdma_dac1_ch1) & HAL_DMA_STATE_BUSY)
  {
    if (HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1) != HAL_OK)
    {
      STATE_setError(&state, DAC_STOP_FAILURE);
      return;
    }
  }

  if (HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t *)buffer, len, DAC_ALIGN_12B_R) != HAL_OK)
  {
    STATE_setError(&state, DAC_START_FAILURE);
    return;
  }
}

void Drivers::setDAC1_2(const uint16_t value)
{
  if (HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2) != HAL_OK)
  {
    STATE_setError(&state, DAC_START_FAILURE);
    return;
  }

  if (HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_12B_R, (uint32_t)value) != HAL_OK)
  {
    STATE_setError(&state, DAC_SET_FAILURE);
    return;
  }
}

// GPIO
void Drivers::GPIO_IAC(const bool state)
{
  HAL_GPIO_WritePin(IAC_RESET_GPIO_Port, IAC_RESET_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Drivers::GPIO_VAC(const bool state)
{
  HAL_GPIO_WritePin(IAC_RESET_GPIO_Port, VAC_RESET_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Drivers::GPIO_IDENT(const bool state)
{
  HAL_GPIO_WritePin(IDENTIFY_LED_GPIO_Port, IDENTIFY_LED_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Utils
void Drivers::getUniqueId(uint32_t *uid)
{
  uid[0] = HAL_GetUIDw0();
  uid[1] = HAL_GetUIDw1();
  uid[2] = HAL_GetUIDw2();
}
