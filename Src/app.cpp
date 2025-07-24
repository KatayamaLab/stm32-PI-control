#include "app.hpp"

void App::main()
{

  // Check command buffer
  if (STATE_getCmdAvailable(&state))
  {
    PROCESS_COMMAND();
  }

  // Check send data
  SEND_DATA();

  switch (STATE_getState(&state))
  {

  case ANALYZER_IDLE:
    return;

  case ANALYZER_WAIT:
    Mmt::WAIT();
    return;

  case ANALYZER_DC:
    Mmt::DC();
    return;

  case ANALYZER_AC:
    Mmt::AC();
    return;

  case ANALYZER_HPF:
    Mmt::SET_HPF();
    return;

  case ANALYZER_VOFFSET:
    Mmt::SET_VOFFSET();
    return;

  case ANALYZER_MEASURE_AC:
    Mmt::MEASURE_AC();
    return;
  
  case ANALYZER_CALIBRATE_CURRENT:
    Mmt::CALIBRATE_CURRENT();
    return;

  case ANALYZER_MEASURE_DC:
    Mmt::MEASURE_DC();
    return;

  case ANALYZER_WHOAMI:
    Mmt::WHOAMI();
    return;

  default:
    return;
  }
}

void App::SEND_DATA()
{
  // データ読み取り禁止の場合
  if (!STATE_getDataAvailable(&state))
  {
    return;
  }

  // 送信データ数が0の場合
  if (STATE_getSendDataLength(&state) == 0)
  {
    return;
  }

  // データ数が奇数の場合は送信しない（電流と電圧セット）
  if (STATE_getAvailableDataLen(&state) % 2 != 0)
  {
    return;
  }

  // カウンタを減算
  STATE_decrementSendDataLength(&state);
  STATE_decrementSendDataLength(&state);

  // 2データだけ送信
  int16_t data[2];
  int len = STATE_readData(&state, data, 2);

  // データなし
  if (len == 0)
  {
    return;
  }

  CLI::print(data[0]);
  CLI::print(",");
  CLI::print(data[1]);

  AnalyzerStateTypeDef nowState = STATE_getState(&state);

  // 特定のコマンドでは改行する
  if (nowState == ANALYZER_WAIT_MEASURE || nowState == ANALYZER_CHARGE_CC || nowState == ANALYZER_CHARGE_CCCV ||
      STATE_getSendDataLength(&state) == 0)
  {
    CLI::println("");
  }
  else
  {
    CLI::print(",");
  }
}

void App::PROCESS_COMMAND()
{
  // Get command
  char command[MAX_LINE_LENGTH];
  float params[MAX_PARAM_NUM];
  int paramNum = CLI::getCommand(command, params);

  // 状態遷移なし
  // Getter
  if (strcmp(command, "s?") == 0)
  {
    // 状態, エラー, 利用可能なデータ数
    CLI::printState(&state);
    return;
  }

  if (strcmp(command, "d?") == 0)
  {
    // データ数指定がある場合はその数だけデータを読み込む
    int len = paramNum == 1 ? (int)params[0] : STATE_getAvailableDataLen(&state);
    STATE_setSendDataLength(&state, len);
    return;
  }

  if (strcmp(command, "uid?") == 0)
  {
    uint32_t uid[3];
    Mmt::getUniqueId(uid);

    CLI::print(uid[0]);
    CLI::print(",");
    CLI::print(uid[1]);
    CLI::print(",");
    CLI::print(uid[2]);
    CLI::println("");

    return;
  }

  // 再起動
  if (strcmp(command, "abort") == 0)
  {
    // 強制リセット
    HAL_NVIC_SystemReset();
    return;
  }
  // ここまで状態を変える

  // Setter

  if (strcmp(command, "enac") == 0)
  {
    // Enable AC
    Mmt::setAcEnable(params, paramNum);
    return;
  }

  if (strcmp(command, "pwm") == 0)
  {
    Mmt::setPWMWaveConfig(params, paramNum);
    return;
  }

  if (strcmp(command, "mtimer") == 0)
  {
    Mmt::setTimerConfig(params, paramNum);
    return;
  }

  if (strcmp(command, "ptimer") == 0)
  {
    Mmt::setPWMTimerConfig(params, paramNum);
    return;
  }

  if (strcmp(command, "lpwm") == 0)
  {
    Mmt::setPWMLoad(params, paramNum);
    return;
  }

  if (strcmp(command, "swtimer") == 0)
  {
    Mmt::setSWTimerConfig(params, paramNum);
    return;
  }

  if (strcmp(command, "echo") == 0)
  {
    STATE_setEchoBack(&state, params[0]);
    return;
  }

  if (strcmp(command, "setpi") == 0)
  {
    Mmt::setKpKi(params, paramNum);
    return;
  }

  STATE_setError(&state, COMMAND_NOT_FOUND);

  // 直前のコマンドが終了するまで新たな状態遷移コマンドを受け付けない
  if (STATE_getState(&state) != ANALYZER_IDLE && STATE_getState(&state) != ANALYZER_COMPLETE)
  {
    return;
  }

  STATE_clearError(&state);

  // 状態遷移あり
  if (strcmp(command, "mac") == 0)
  {
    // インピーダンス測定
    STATE_push(&state, ANALYZER_MEASURE_AC, params, paramNum);
    return;
  }
  // 電流制御のコマンド
  if (strcmp(command, "current") == 0)
  {
    // インピーダンス測定
    STATE_push(&state, ANALYZER_CALIBRATE_CURRENT, params, paramNum);
    return;
  } 

  if (strcmp(command, "hpf") == 0)
  {
    // HPFリセット
    STATE_push(&state, ANALYZER_HPF, params, paramNum);
    return;
  }

  if (strcmp(command, "voffset") == 0)
  {
    STATE_push(&state, ANALYZER_VOFFSET, params, paramNum);
    return;
  }

  if (strcmp(command, "mdc") == 0)
  {
    // 単発測定
    STATE_push(&state, ANALYZER_MEASURE_DC, params, paramNum);
    return;
  }

  if (strcmp(command, "whoami") == 0)
  {
    STATE_push(&state, ANALYZER_WHOAMI, params, paramNum);
    return;
  }

  STATE_setError(&state, COMMAND_NOT_FOUND);
}
