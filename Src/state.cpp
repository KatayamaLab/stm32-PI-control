#include "state.h"

// State
AnalyzerStateTypeDef STATE_getState(State *state)
{
  return state->state.s[state->state.top];
}

void STATE_setState(State *state, AnalyzerStateTypeDef newState)
{
  state->state.s[state->state.top] = newState;
}

float *STATE_getParams(State *state)
{
  return state->state.params[state->state.top];
}

int STATE_getParamNum(State *state)
{
  return state->state.paramNum[state->state.top];
}

// Num
void *STATE_getNum(State *state, uint8_t idx)
{
  return state->state.ptr[state->state.top][idx];
}

void STATE_makeNum(State *state, uint8_t idx, uint8_t size)
{
  // メモリの確保と初期化
  void *ptr = calloc(1, size);

  if (ptr == NULL)
  {
    state->error = MEMORY_ALLOCATION_FAILURE;
    return;
  }

  // すでに値が存在している場合は解放する
  STATE_freeNum(state, idx);

  state->state.ptr[state->state.top][idx] = ptr;
}

void STATE_freeNum(State *state, uint8_t idx)
{
  void *ptr = state->state.ptr[state->state.top][idx];

  if (ptr != NULL)
  {
    // 解放と上書き
    free(ptr);
    state->state.ptr[state->state.top][idx] = NULL;
  }
}

void STATE_init(State *state, int16_t *dataBuff, uint16_t *pwmBuff)
{
  // Initialize top
  state->state.top = 0;

  // Initialize state
  state->state.s[0] = ANALYZER_IDLE;

  // Initialize internal state
  state->internalState = ANALYZER_INTERNAL_READY;

  // Initialize error
  state->error = NO_ERROR;

  // Initialize handle data
  state->hdata.isAvailable = false;
  state->hdata.idx = 0;
  state->hdata.ptr = dataBuff;
  state->hdata.len = 0;

  // Initialize pwm
  state->pwm.ptr = pwmBuff;
  state->pwm.len = 0;
  state->pwm.idx = 0;

  // Initialize command
  state->cmdAvailable = false;

  // Initialize echo back
  state->isEchoBack = false;
}

void STATE_push(State *state, AnalyzerStateTypeDef newState, float *params, int paramNum)
{
  // Increment top
  state->state.top++;

  if (state->state.top >= MAX_STACK_NUM)
  {
    state->error = STACK_OVERFLOW;
    return;
  }

  // Set state
  state->state.s[state->state.top] = newState;

  // Set params
  memcpy(state->state.params[state->state.top], params, paramNum * sizeof(float));
  state->state.paramNum[state->state.top] = paramNum;

  // Reset sequence counter
  state->state.seqCtr[state->state.top] = 0;
}

void STATE_pop(State *state)
{
  // Decrement top
  state->state.top--;

  if (state->state.top < 0)
  {
    state->error = STACK_UNDERFLOW;
    return;
  }
}

// Internal
void STATE_setInternalState(State *state, AnalyzerInternalStateTypeDef newInternalState)
{
  state->internalState = newInternalState;
}

AnalyzerInternalStateTypeDef STATE_getInternalState(State *state)
{
  return state->internalState;
}

// Error
void STATE_setError(State *state, AnalyzerErrorTypeDef newError)
{
  state->error = newError;
}

AnalyzerErrorTypeDef STATE_getError(State *state)
{
  return state->error;
}

bool STATE_hasError(State *state)
{
  return state->error != NO_ERROR;
}

void STATE_clearError(State *state)
{
  state->error = NO_ERROR;
}
// Data

int STATE_getAvailableDataLen(State *state)
{
  return state->hdata.len;
}

bool STATE_getDataAvailable(State *state)
{
  return state->hdata.isAvailable;
}

void STATE_setDataAvailable(State *state)
{
  state->hdata.isAvailable = true;
}

void STATE_resetDataAvailable(State *state)
{
  state->hdata.isAvailable = false;
}

void STATE_clearData(State *state)
{
  state->hdata.idx = 0;
  state->hdata.len = 0;
}

void STATE_writeData(State *state, int16_t *data, int len)
{
  if (len <= 0 || len > DATA_BUFFER_SIZE || data == NULL)
  {
    state->error = WRITE_DATA_FAILURE;
    return;
  }

  AnalyzerHandleDataTypeDef *hdata = &state->hdata;

  // 書き込み開始位置
  int writeStartIdx = hdata->idx + hdata->len;
  for (int idx = 0; idx < len; idx++)
  {
    hdata->ptr[(writeStartIdx + idx) % DATA_BUFFER_SIZE] = data[idx];
  }

  // データの上書きが発生した場合は読み込み開始位置を更新する
  if (hdata->len + len > DATA_BUFFER_SIZE)
  {
    hdata->idx = (hdata->idx + len) % DATA_BUFFER_SIZE;
  }

  // データ長を更新
  hdata->len += len;
  if (hdata->len > DATA_BUFFER_SIZE)
  {
    hdata->len = DATA_BUFFER_SIZE;
  }
}

int STATE_readData(State *state, int16_t *data, int len)
{
  if (len <= 0)
  {
    return 0;
  }

  AnalyzerHandleDataTypeDef *hdata = &state->hdata;

  if (len > hdata->len)
  {
    // 書き込まれたデータより大きいデータが要求された場合は最大まで読み込む
    len = hdata->len;
  }

  // 読み込み開始位置
  int readStartIdx = hdata->idx;
  for (int idx = 0; idx < len; idx++)
  {
    data[idx] = hdata->ptr[(readStartIdx + idx) % DATA_BUFFER_SIZE];
  }

  // 読み込み開始位置を更新
  hdata->idx = (readStartIdx + len) % DATA_BUFFER_SIZE;

  // データ長を更新
  hdata->len -= len;

  // 読み込んだデータ数
  return len;
}

void STATE_setSendDataLength(State *state, int len)
{
  state->hdata.sendDataLength = len;
}

int STATE_getSendDataLength(State *state)
{
  return state->hdata.sendDataLength;
}

void STATE_decrementSendDataLength(State *state)
{
  state->hdata.sendDataLength--;
}

// PWM
uint16_t *STATE_getPWMBuff(State *state)
{
  return state->pwm.ptr;
}

void STATE_setPWMLen(State *state, int len)
{
  state->pwm.len = len;
}

int STATE_getPWMIdx(State *state)
{
  return state->pwm.idx;
}

bool STATE_isPWMLastIndex(State *state)
{
  AnalyzerPWMConfigTypeDef *pwm = &state->pwm;
  // 現在のインデックスが最後のインデックスかどうかを判定
  if (pwm->idx >= pwm->len - 1)
  {
    return true;
  }

  return false;
}

void STATE_incrementPWMIdx(State *state)
{
  // 最後のインデックスの場合は0に戻る
  if (STATE_isPWMLastIndex(state))
  {
    state->pwm.idx = 0;
    return;
  }

  state->pwm.idx++;
}

void STATE_resetPWMIdx(State *state)
{
  state->pwm.idx = 0;
}

// Unique data
void STATE_setKp(State *state, float newKp)
{
  state->uniqueData.Kp = newKp;
}
void STATE_setKi(State *state, float newKi)
{
  state->uniqueData.Ki = newKi;
}

void STATE_getFeedbackGain(State *state, float *Kp, float *Ki)
{
  *Kp = state->uniqueData.Kp;
  *Ki = state->uniqueData.Ki;
}

// cmd
bool STATE_getCmdAvailable(State *state)
{
  return state->cmdAvailable;
}

void STATE_setCmdAvailable(State *state)
{
  state->cmdAvailable = true;
}

void STATE_resetCmdAvailable(State *state)
{
  state->cmdAvailable = false;
}

// Ctr
uint8_t STATE_getSeqCtr(State *state)
{
  return state->state.seqCtr[state->state.top];
}

void STATE_setSeqCtr(State *state, uint8_t ctr)
{
  state->state.seqCtr[state->state.top] = ctr;
}

void STATE_incrementSeqCtr(State *state)
{
  state->state.seqCtr[state->state.top]++;
}

void STATE_decrementSeqCtr(State *state)
{
  state->state.seqCtr[state->state.top]--;
}

void STATE_resetSeqCtr(State *state)
{
  state->state.seqCtr[state->state.top] = 0;
}

bool STATE_getEchoBack(State *state)
{
  return state->isEchoBack;
}

void STATE_setEchoBack(State *state, bool isEchoBack)
{
  state->isEchoBack = isEchoBack;
}