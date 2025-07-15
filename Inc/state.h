#ifndef _STATE_HPP_
#define _STATE_HPP_

#include "code_def.h"
#include "const.h"
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
  // State code
  AnalyzerStateTypeDef s[MAX_STACK_NUM];

  // parameter
  float params[MAX_STACK_NUM][MAX_PARAM_NUM];
  int paramNum[MAX_STACK_NUM];

  // sequence control counter
  uint8_t seqCtr[MAX_STACK_NUM];

  // multi purpose num
  void *ptr[MAX_STACK_NUM][MAX_PARAM_NUM];

  // Stack top position
  int top;

} AnalyzerStateStackTypeDef;

typedef struct
{
  // Whether the data is available
  bool isAvailable;
  // 送信データ数
  int sendDataLength;
  // Start index of current data
  int idx;
  // Length of data in buffer
  int len;
  // Buffer
  int16_t *ptr;

} AnalyzerHandleDataTypeDef;

typedef struct
{
  // PWM関連のデータを保持する

  // PWMバッファのポインタ
  uint16_t *ptr;
  // PWMバッファの長さ
  int len;
  // 現在のインデックス
  int idx;

} AnalyzerPWMConfigTypeDef;

typedef struct
{
  // フィードバックゲイン
  // 比例ゲイン
  float Kp = 0.3;
  // 積分ゲイン
  float Ki = 0.8;

} AnalyzerUniqueDataTypeDef;

typedef struct
{
  // State stack
  AnalyzerStateStackTypeDef state;
  // Internal state
  AnalyzerInternalStateTypeDef internalState;
  // Error code
  AnalyzerErrorTypeDef error;
  // Data for transmission
  AnalyzerHandleDataTypeDef hdata;
  // PWM data
  AnalyzerPWMConfigTypeDef pwm;
  // Unique data
  AnalyzerUniqueDataTypeDef uniqueData;

  // Command availability flag
  bool cmdAvailable;
  // Echo back flag
  bool isEchoBack;
} State;

// ################ Function prototypes ################
// State
AnalyzerStateTypeDef STATE_getState(State *state);
float *STATE_getParams(State *state);
int STATE_getParamNum(State *state);
void STATE_init(State *state, int16_t *dataBuffer, uint16_t *pwmBuffer);
void STATE_setState(State *state, AnalyzerStateTypeDef newState);
void STATE_push(State *state, AnalyzerStateTypeDef newState, float *params, int paramNum);
void STATE_pop(State *state);

// Num
void *STATE_getNum(State *state, uint8_t idx);
void STATE_makeNum(State *state, uint8_t idx, uint8_t size);
void STATE_freeNum(State *state, uint8_t idx);

// Internal
AnalyzerInternalStateTypeDef STATE_getInternalState(State *state);
void STATE_setInternalState(State *state, AnalyzerInternalStateTypeDef newInternalState);

// Error
AnalyzerErrorTypeDef STATE_getError(State *state);
void STATE_setError(State *state, AnalyzerErrorTypeDef newError);
bool STATE_hasError(State *state);
void STATE_clearError(State *state);

// Data
int STATE_getAvailableDataLen(State *state);
bool STATE_getDataAvailable(State *state);
void STATE_setDataAvailable(State *state);
void STATE_resetDataAvailable(State *state);
void STATE_clearData(State *state);
void STATE_writeData(State *state, int16_t *data, int len);
int STATE_readData(State *state, int16_t *data, int len);
void STATE_setSendDataLength(State *state, int len);
int STATE_getSendDataLength(State *state);
void STATE_decrementSendDataLength(State *state);

// PWM
int STATE_getPWMIdx(State *state);
uint16_t *STATE_getPWMBuff(State *state);
bool STATE_isPWMLastIndex(State *state);
void STATE_setPWMLen(State *state, int len);
void STATE_incrementPWMIdx(State *state);
void STATE_resetPWMIdx(State *state);

// Unique data
void STATE_setKp(State *state, float newKp);
void STATE_setKi(State *state, float newKi);
void STATE_getFeedbackGain(State *state, float *Kp, float *Ki);


// cmd
bool STATE_getCmdAvailable(State *state);
void STATE_setCmdAvailable(State *state);
void STATE_resetCmdAvailable(State *state);

// Ctr
uint8_t STATE_getSeqCtr(State *state);
void STATE_setSeqCtr(State *state, uint8_t ctr);
void STATE_incrementSeqCtr(State *state);
void STATE_decrementSeqCtr(State *state);
void STATE_resetSeqCtr(State *state);

// Echo back
bool STATE_getEchoBack(State *state);
void STATE_setEchoBack(State *state, bool isEchoBack);

extern State state;

#endif
