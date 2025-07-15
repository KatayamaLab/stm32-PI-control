#include "measurement.hpp"

uint16_t Mmt::pwmBuffer[MAX_BUFFER_SIZE];
uint16_t Mmt::adcBuffer[2 * MAX_BUFFER_SIZE];
int16_t Mmt::dataBuffer[DATA_BUFFER_SIZE];

uint16_t *Mmt::currentBuffer = Mmt::adcBuffer;
uint16_t *Mmt::voltageBuffer = Mmt::adcBuffer + MAX_BUFFER_SIZE;

// ポインタの初期化
uint16_t *pwmBuffer = pwmBuffer;

void Mmt::WAIT()
{
  /*
      指定した時間待機する
      待機中は何もしない

      Errors:
          MEMORY_ALLOCATION_FAILURE

  */

  // エラーチェック
  if (STATE_hasError(&state))
  {
    // 終了処理

    // 親状態に処理を戻す
    STATE_pop(&state);
    return;
  }

  int ctr = STATE_getSeqCtr(&state);

  float *params = STATE_getParams(&state);

  if (ctr == 0)
  {
    // 　親状態によって正確なパラメータが入力されることが保証される

    // メモリの確保
    // StartTime
    STATE_makeNum(&state, 0, sizeof(uint32_t));

    if (STATE_hasError(&state))
    {
      return;
    }

    // スタート時間の取得
    uint32_t *startTime = (uint32_t *)STATE_getNum(&state, 0);
    *startTime = HAL_GetTick();

    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 1)
  {
    // milisecond
    uint32_t time = (uint32_t)params[0];

    // スタート時間の取得
    uint32_t *startTime = (uint32_t *)STATE_getNum(&state, 0);

    // スタート時間からの経過時間の取得
    if (HAL_GetTick() - *startTime < time)
    {
      return;
    }

    // メモリの解放
    // StartTime
    STATE_freeNum(&state, 0);

    // 状態のポップ
    STATE_pop(&state);
  }
}

void Mmt::DC()
{
  /*

      Errors:
          MEMORY_ALLOCATION_FAILURE
          ADC_START_FAILURE
          ADC_STOP_FAILURE
          ADC_MULTIMODE_SET_FAILURE
          ADC_CHANNEL_SET_FAILURE
          ADC_DMA_TRANSFER_FAILURE
          ADC_INTERNAL_FAILURE
          ADC_OVERRUN_FAILURE
  */

  if (STATE_hasError(&state))
  {
    // 　親状態に処理を戻す
    STATE_pop(&state);
    return;
  }

  int ctr = STATE_getSeqCtr(&state);

  // parameter
  float *params = STATE_getParams(&state);

  if (ctr == 0)
  {
    // 親状態によって正確なパラメータが入力されることが保証される
    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 1)
  {
    int len = (int)params[0];

    // Current
    Drivers::getADC1_1_DMA(currentBuffer, len);
    if (STATE_hasError(&state))
    {
      return;
    }

    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 2)
  {
    // Wait for conversion finish
    if (STATE_getInternalState(&state) != ANALYZER_INTERNAL_COMPLETE)
    {
      return;
    }

    int len = (int)params[0];

    // Voltage
    Drivers::getADC1_2_DMA(voltageBuffer, len);
    if (STATE_hasError(&state))
    {
      return;
    }

    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 3)
  {

    // Wait for second conversion finish
    if (STATE_getInternalState(&state) != ANALYZER_INTERNAL_COMPLETE)
    {
      return;
    }

    STATE_pop(&state);
    return;
  }
}

void Mmt::AC()
{
  if (STATE_hasError(&state))
  {
    // 親状態に処理を戻す
    STATE_pop(&state);
    return;
  }

  // parameter
  float *params = STATE_getParams(&state);

  int ctr = STATE_getSeqCtr(&state);

  if (ctr == 0)
  {
    // 親状態によって正確なパラメータが入力されることが保証される
    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 1)
  {
    int len = (int)params[0];

    Drivers::getADC_Dual(adcBuffer, len);
    if (STATE_hasError(&state))
    {
      return;
    }

    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 2)
  {
    if (STATE_getInternalState(&state) != ANALYZER_INTERNAL_COMPLETE)
    {
      return;
    }

    STATE_pop(&state);
    return;
  }
}

void Mmt::MEASURE_DC()
{

  /*

      Errors:
          INVALID_PARAMETER_NUM
          INVALID_PARAMETER_RANGE
          ADC_START_FAILURE
          ADC_STOP_FAILURE
          ADC_MULTIMODE_SET_FAILURE,
          ADC_CHANNEL_SET_FAILURE,
          ADC_DMA_TRANSFER_FAILURE,
          ADC_INTERNAL_FAILURE,
          ADC_OVERRUN_FAILURE,
  */

  // Error check
  if (STATE_hasError(&state))
  {
    // 終了処理
    STATE_pop(&state);
    return;
  }

  // Get sequence counter
  int ctr = STATE_getSeqCtr(&state);

  float *params = STATE_getParams(&state);

  // First loop
  if (ctr == 0)
  {
    // Validate parameter
    if (STATE_getParamNum(&state) != 1)
    {
      STATE_setError(&state, INVALID_PARAMETER_NUM);
      return;
    }

    int len = (int)params[0];

    if (len <= 0 || len > MAX_BUFFER_SIZE)
    {
      STATE_setError(&state, INVALID_PARAMETER_RANGE);
      return;
    }

    STATE_incrementSeqCtr(&state);

    // Reset data available flag
    STATE_resetDataAvailable(&state);

    float params[1] = {(float)len};
    STATE_push(&state, ANALYZER_DC, params, 1);

    return;
  }
  else if (ctr == 1)
  {

    int len = (int)params[0];

    // Averaging
    uint16_t current = 0;
    uint16_t voltage = 0;

    average(currentBuffer, len, &current);
    average(voltageBuffer, len, &voltage);

    // Set data to state
    int16_t data[2];
    data[0] = current;
    data[1] = voltage;
    STATE_writeData(&state, data, 2);

    // Set data available flag
    STATE_setDataAvailable(&state);

    // Pop state
    STATE_pop(&state);

    // Set state to complete
    STATE_setState(&state, ANALYZER_COMPLETE);

    return;
  }
}

void Mmt::MEASURE_AC()
{

  /*

      Errors:
          INVALID_PARAMETER_NUM
          INVALID_PARAMETER_RANGE
          ADC_MULTIMODE_SET_FAILURE,
          ADC_CHANNEL_SET_FAILURE,
          ADC_DMA_TRANSFER_FAILURE,
          ADC_INTERNAL_FAILURE,
          ADC_OVERRUN_FAILURE,
  */

  if (STATE_hasError(&state))
  {
    // 終了処理
    STATE_pop(&state);
    return;
  }

  // Get sequence counter
  int ctr = STATE_getSeqCtr(&state);

  float *params = STATE_getParams(&state);

  if (ctr == 0)
  {

    if (STATE_getParamNum(&state) != 1)
    {
      STATE_setError(&state, INVALID_PARAMETER_NUM);
    }

    int len = (int)params[0];

    if (len <= 0 || len > MAX_BUFFER_SIZE)
    {
      STATE_setError(&state, INVALID_PARAMETER_RANGE);
      return;
    }

    STATE_incrementSeqCtr(&state);

    // Reset data buffer
    STATE_clearData(&state);

    // Reset data available flag
    STATE_resetDataAvailable(&state);

    float params[1] = {(float)len};
    STATE_push(&state, ANALYZER_AC, params, 1);

    return;
  }
  else if (ctr == 1)
  {

    // Transfer data
    int len = (int)params[0];

    STATE_writeData(&state, (int16_t *)adcBuffer, 2 * len);

    // voltage and current
    STATE_setDataAvailable(&state);

    // Pop state
    STATE_pop(&state);

    // Set state to complete
    STATE_setState(&state, ANALYZER_COMPLETE);

    return;
  }
}

void Mmt::SET_HPF()
{

  /*

      Errors:
          INVALID_PARAMETER_NUM
          MEMORY_ALLOCATION_FAILURE  (ANALYZER_WAIT)
  */
  // Get sequence counter
  int ctr = STATE_getSeqCtr(&state);

  if (STATE_hasError(&state))
  {
    // 終了処理を行う
    Drivers::GPIO_IAC(false);
    Drivers::GPIO_VAC(false);

    STATE_pop(&state);
    return;
  }

  if (ctr == 0)
  {

    if (STATE_getParamNum(&state) != 0)
    {
      STATE_setError(&state, INVALID_PARAMETER_NUM);
      return;
    }

    STATE_incrementSeqCtr(&state);

    return;
  }
  else if (ctr == 1)
  {

    Drivers::GPIO_IAC(true);
    Drivers::GPIO_VAC(true);

    // increment timer state ctr
    STATE_incrementSeqCtr(&state);

    // Wait for 200ms (fixed)
    float params[1] = {(float)200};
    STATE_push(&state, ANALYZER_WAIT, params, 1);

    return;
  }
  else if (ctr == 2)
  {

    Drivers::GPIO_IAC(false);
    Drivers::GPIO_VAC(false);

    // Pop state
    STATE_pop(&state);

    // Set state to complete
    STATE_setState(&state, ANALYZER_COMPLETE);

    return;
  }
}

void Mmt::SET_VOFFSET()
{

  /*
      Errors:
          INVALID_PARAMETER_NUM
          INVALID_PARAMETER_RANGE
          ADC_START_FAILURE
          ADC_STOP_FAILURE
          ADC_MULTIMODE_SET_FAILURE,
          ADC_CHANNEL_SET_FAILURE,
          ADC_DMA_TRANSFER_FAILURE,
          ADC_INTERNAL_FAILURE,
          ADC_OVERRUN_FAILURE,
  */

  if (STATE_hasError(&state))
  {
    // 終了処理
    STATE_pop(&state);
    return;
  }

  // Get sequence counter
  int ctr = STATE_getSeqCtr(&state);

  float *params = STATE_getParams(&state);

  if (ctr == 0)
  {
    // Validate parameter
    if (STATE_getParamNum(&state) != 1)
    {
      STATE_setError(&state, INVALID_PARAMETER_NUM);
      return;
    }

    int len = (int)params[0];

    if (len <= 0 || len > MAX_BUFFER_SIZE)
    {
      STATE_setError(&state, INVALID_PARAMETER_RANGE);
      return;
    }

    Drivers::getADC1_2_DMA(adcBuffer, len);
    if (STATE_hasError(&state))
    {
      return;
    }

    STATE_incrementSeqCtr(&state);

    return;
  }

  else if (ctr == 1)
  {
    if (STATE_getInternalState(&state) != ANALYZER_INTERNAL_COMPLETE)
    {
      return;
    }

    int len = (int)params[0];

    float offset = 0;

    for (int i = 0; i < len; i++)
    {
      offset += adcBuffer[2 * i];
    }

    offset /= len;

    Drivers::setDAC1_2((uint16_t)(offset * 4.0 / 3.0));
    if (STATE_hasError(&state))
    {
      return;
    }

    // Pop state
    STATE_pop(&state);

    // Set state to complete
    STATE_setState(&state, ANALYZER_COMPLETE);

    return;
  }
}

void Mmt::WHOAMI()
{
  if (STATE_hasError(&state))
  {
    return;
  }

  int ctr = STATE_getSeqCtr(&state);
  // 現在時刻
  uint32_t now = HAL_GetTick();

  float *params = STATE_getParams(&state);

  if (ctr == 0)
  {

    if (STATE_getParamNum(&state) != 1)
    {
      STATE_setError(&state, INVALID_PARAMETER_NUM);
      return;
    }

    if (params[0] <= 0)
    {
      STATE_setError(&state, INVALID_PARAMETER_RANGE);
      return;
    }

    /*
        num
            num[0]: counter
            num[1]: waitStartTime
    */

    STATE_makeNum(&state, 0, sizeof(uint32_t));
    STATE_makeNum(&state, 1, sizeof(uint32_t));

    if (STATE_hasError(&state))
    {
      return;
    }

    uint32_t *counter = (uint32_t *)STATE_getNum(&state, 0);
    *counter = (uint32_t)params[0];

    // シーケンスカウンタを増加
    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 1)
  {

    uint32_t *waitStartTime = (uint32_t *)STATE_getNum(&state, 1);
    *waitStartTime = now;

    // blink led
    Drivers::GPIO_IDENT(true);

    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 2)
  {

    uint32_t *waitStartTime = (uint32_t *)STATE_getNum(&state, 1);

    if (now - *waitStartTime < 500)
    {
      return;
    }

    // blink led
    Drivers::GPIO_IDENT(false);

    *waitStartTime = now;

    STATE_incrementSeqCtr(&state);
    return;
  }
  else if (ctr == 3)
  {

    uint32_t *waitStartTime = (uint32_t *)STATE_getNum(&state, 1);

    if (now - *waitStartTime < 500)
    {
      return;
    }

    // カウンターを減少
    uint32_t *counter = (uint32_t *)STATE_getNum(&state, 0);
    *counter -= 1;

    if (*counter == 0)
    {

      // メモリの解放
      STATE_freeNum(&state, 0);
      STATE_freeNum(&state, 1);

      STATE_pop(&state);

      // Set state to complete
      STATE_setState(&state, ANALYZER_COMPLETE);

      return;
    }

    STATE_setSeqCtr(&state, 1);

    return;
  }
}

void Mmt::CALIBRATE_CURRENT()
{
  if (STATE_hasError(&state))
  {
    STATE_pop(&state);
    return;
  }

  int ctr = STATE_getSeqCtr(&state);
  // 現在時刻
  uint32_t now = HAL_GetTick();

  float *params = STATE_getParams(&state);

  if (ctr == 0)
  {

    if (STATE_getParamNum(&state) != 7)
    {
      STATE_setError(&state, INVALID_PARAMETER_NUM);
      return;
    }

    /*
      parameters
        param[0]: iteration number
        param[1]: timestep [ms]
        param[2]: current measure buffer size
        param[3]: amplitude
        param[4]: offset initial value
        param[5]: wave num
        param[6]: pwm buffer length
    */

    if (params[0] <= 0 || params[1] <= 0)
    {
      STATE_setError(&state, INVALID_PARAMETER_RANGE);
      return;
    }

    /*
      num
          num[0]: curernt iteration
          num[1]: interval start
          num[2]: previous dac value
          num[3]: previous error
    */

    STATE_makeNum(&state, 0, sizeof(uint32_t));
    STATE_makeNum(&state, 1, sizeof(uint32_t));
    STATE_makeNum(&state, 2, sizeof(uint16_t));
    STATE_makeNum(&state, 3, sizeof(uint16_t));

    if (STATE_hasError(&state))
    {
      return;
    }

    // 現在時刻を設定
    uint32_t *intervalStart = (uint32_t *)STATE_getNum(&state, 1);
    *intervalStart = now;

    // バッファの初期値を設定
    float pwmConfigParams[4] = {params[3], params[4], params[5], params[6]};
    Mmt::setPWMWaveConfig(pwmConfigParams, 4);

    // PWMを有効化
    float loadParam[1] = {1};
    Mmt::setPWMLoad(loadParam, 1);

    STATE_incrementSeqCtr(&state);
  }
  else if (ctr == 1)
  {
    uint32_t *intervalStart = (uint32_t *)STATE_getNum(&state, 1);
    uint32_t timestep = (uint32_t)params[1];

    // 次のタイムステップまで待機
    if (now - timestep > *intervalStart)
    {

      STATE_incrementSeqCtr(&state);

      // Reset data buffer
      STATE_clearData(&state);

      // AC測定を実行
      float len = params[2];
      float params[1] = {len};
      STATE_push(&state, ANALYZER_AC, params, 1);
    }
  }
  else if (ctr == 2)
  {

    int len = (int)params[2];

    uint32_t iterationNum = (uint32_t)params[0];
    uint32_t *currentIteration = (uint32_t *)STATE_getNum(&state, 0);

    // Averaging current
    uint16_t current = 0;
    average(currentBuffer, len, &current);

    // #################### フィードバック制御 #########################

    // ############################################################
    // 比例定数
    float Kp;
    // 積分定数
    float Ki;

    STATE_getFeedbackGain(&state, &Kp, &Ki);

    // ############################################################

    // 制御時間ステップ [ms]
    float interval = params[1];
    // 前ステップの電流値 [mA]
    float *prevDacCount = (float *)STATE_getNum(&state, 2);
    // 前ステップの誤差 [mA]
    float *prevError = (float *)STATE_getNum(&state, 3);

    // 電流の偏差
    float error = 0 - current;

    // 電流のオフセットの計算
    float nextDacCount = *prevDacCount + Kp * (error - *prevError) + Ki * (interval / 1000.0) * error;

    float pwmConfigParams[4] = {params[3], nextDacCount, params[5], params[6]};
    Mmt::setPWMWaveConfig(pwmConfigParams, 4);

    // 値の更新
    *prevDacCount = nextDacCount;
    *prevError = error;

    // ############################################################

    *currentIteration++;

    if (*currentIteration >= iterationNum)
    {
      // Pop state
      STATE_pop(&state);

      // Set state to complete
      STATE_setState(&state, ANALYZER_COMPLETE);

      // PWMを無効化
      float loadParam[1] = {0};
      Mmt::setPWMLoad(loadParam, 1);

      return;
    }

    // インターバルの開始時間を更新
    uint32_t *intervalStart = (uint32_t *)STATE_getNum(&state, 1);
    *intervalStart = now;

    STATE_decrementSeqCtr(&state);
  }
}

// Setter
void Mmt::getUniqueId(uint32_t *uid)
{
  Drivers::getUniqueId(uid);
}

void Mmt::setAcEnable(float *params, int paramNum)
{
  if (paramNum != 1)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }

  if (params[0])
  {
    Drivers::GPIO_IAC(false);
    Drivers::GPIO_VAC(false);
    return;
  }
  else
  {
    Drivers::GPIO_IAC(true);
    Drivers::GPIO_VAC(true);
    return;
  }
  STATE_setState(&state, ANALYZER_COMPLETE);
}

void Mmt::setSWTimerConfig(float *params, int paramNum)
{
  if (paramNum != 2)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }
  uint16_t swpsc = (uint16_t)params[0];
  uint16_t swarr = (uint16_t)params[1];

  if (swpsc <= 0 || swpsc > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  if (swarr <= 1 || swarr > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  Drivers::updateTimer16Config(swpsc, swarr);

  STATE_setState(&state, ANALYZER_COMPLETE);
}

void Mmt::setPWMWaveConfig(float *params, int paramNum)
{

  if (paramNum != 4)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }

  int amp = params[0];
  int offset = params[1];
  int wave = params[2];
  int len = params[3];

  if (amp <= 0 || amp > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  if (offset < 0 || offset > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  if (wave <= 0 || wave > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  if (len <= 0 || len > MAX_BUFFER_SIZE)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  // 波形生成
  for (int i = 0; i < len; i++)
  {
    pwmBuffer[i] = (uint16_t)(amp * sin(2 * PI * i * wave / len) + offset);
  }

  // 状態のセット
  STATE_setPWMLen(&state, len);
  STATE_resetPWMIdx(&state);

  STATE_setState(&state, ANALYZER_COMPLETE);
}

void Mmt::setPWMTimerConfig(float *params, int paramNum)
{
  if (paramNum != 2)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }
  uint16_t psc = (uint16_t)params[0];
  uint16_t arr = (uint16_t)params[1];

  if (psc <= 0 || psc > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  if (arr <= 1 || arr > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  Drivers::updateTimer3Config(psc, arr);

  STATE_setState(&state, ANALYZER_COMPLETE);
}

void Mmt::setTimerConfig(float *params, int paramNum)
{

  if (paramNum != 2)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }

  int psc = params[0];
  int arr = params[1];

  if (psc <= 0 || psc > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  if (arr <= 1 || arr > 0xFFFF)
  {
    STATE_setError(&state, INVALID_PARAMETER_RANGE);
    return;
  }

  Drivers::updateTimer6Config(psc, arr);

  STATE_setState(&state, ANALYZER_COMPLETE);
}

void Mmt::setPWMLoad(float *params, int paramNum)
{
  if (paramNum != 1)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }

  bool pwmstart = (bool)params[0];
  Drivers::GPIO_PWMLOAD(pwmstart);

  STATE_setState(&state, ANALYZER_COMPLETE);
}

void Mmt::setKpKi(float *params, int paramNum)
{
  if (paramNum != 1)
  {
    STATE_setError(&state, INVALID_PARAMETER_NUM);
    return;
  }

  STATE_setKp(&state, params[0]);
  STATE_setKi(&state, params[1]);

  STATE_setState(&state, ANALYZER_COMPLETE);
}

// Utils

void Mmt::average(uint16_t *buffer, int len, uint16_t *result)
{
  uint32_t sum = 0;
  for (int i = 0; i < len; i++)
  {
    sum += buffer[i];
  }

  *result = (uint16_t)(sum / len);
}
