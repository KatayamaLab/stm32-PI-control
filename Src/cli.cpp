#include "cli.hpp"

uint8_t CLI::len = 0;
char CLI::inputLine[MAX_LINE_LENGTH];

static void swap(char *a, char *b)
{
  char t = *a;
  *a = *b;
  *b = t;
}

static char *reverse(char *buf, int i, int j)
{
  while (i < j)
  {
    swap(&buf[i++], &buf[j--]);
  }
  return buf;
}

void CLI::print(const char *buf)
{
  Drivers::uartPutString(buf);
}

void CLI::print(const int val)
{
  char buf[9];
  CLI::itoa(val, buf);
  Drivers::uartPutString(buf);
}

void CLI::print(uint32_t val)
{
  char buf[10];
  CLI::itoa(val, buf);
  Drivers::uartPutString(buf);
}

void CLI::println(const char *buf)
{
  CLI::print(buf);
  Drivers::uartPutString(END_LINE);
}

void CLI::println(const int val)
{
  CLI::print(val);
  Drivers::uartPutString(END_LINE);
}

void CLI::println(const uint32_t val)
{
  CLI::print(val);
  Drivers::uartPutString(END_LINE);
}

void CLI::printState(State *state)
{
  // 状態
  CLI::print(STATE_getState(state));
  CLI::print(",");
  // エラー
  CLI::print(STATE_getError(state));
  CLI::print(",");
  // 利用可能なデータ数
  CLI::print(STATE_getAvailableDataLen(state));
  CLI::println("");
}

char *CLI::itoa(int val, char *buf)
{
  int n = abs(val);

  int i = 0;
  while (n)
  {
    int r = n % 10;
    if (r >= 10)
    {
      buf[i++] = 65 + (r - 10);
    }
    else
    {
      buf[i++] = 48 + r;
    }

    n = n / 10;
  }

  if (i == 0)
  {
    buf[i++] = '0';
  }

  if (val < 0)
  {
    buf[i++] = '-';
  }

  buf[i] = '\0'; // null終了文字列

  return reverse(buf, 0, i - 1);
}

char *CLI::itoa(uint32_t val, char *buf)
{
  uint32_t n = val;

  int i = 0;
  while (n)
  {
    int r = n % 10;
    buf[i++] = 48 + r; // 0-9の範囲での変換
    n = n / 10;
  }

  if (i == 0)
  {
    buf[i++] = '0';
  }

  buf[i] = '\0'; // null終了文字列

  return reverse(buf, 0, i - 1);
}

float CLI::atof(const char *buf)
{
  float result = 0.0;
  bool isNegative = false;
  bool isFraction = false;
  float fractionDivisor = 1.0;
  bool isExponent = false;
  int exponent = 0;
  bool isExponentNegative = false;

  // Handle negative numbers
  if (*buf == '-')
  {
    isNegative = true;
    buf++;
  }

  // Process each character
  while (*buf)
  {
    if (*buf >= '0' && *buf <= '9')
    {
      if (isFraction)
      {
        fractionDivisor *= 10.0;
        result += (*buf - '0') / fractionDivisor;
      }
      else
      {
        result = result * 10.0 + (*buf - '0');
      }
    }
    else if (*buf == '.')
    {
      isFraction = true;
    }
    else if (*buf == 'e' || *buf == 'E')
    {
      isExponent = true;
      buf++;
      if (*buf == '-')
      {
        isExponentNegative = true;
        buf++;
      }
      else if (*buf == '+')
      {
        buf++;
      }
      while (*buf >= '0' && *buf <= '9')
      {
        exponent = exponent * 10 + (*buf - '0');
        buf++;
      }
      break;
    }
    else
    {
      return 0.0;
    }
    buf++;
  }

  // Apply exponent if present
  if (isExponent)
  {
    if (isExponentNegative)
    {
      result /= pow(10, exponent);
    }
    else
    {
      result *= pow(10, exponent);
    }
  }

  return isNegative ? -result : result;
}

bool CLI::getLine(char ch)
{

  // carriage return or line feed
  if (ch == '\r' || ch == '\n')
  {

    if (len == 0)
    {
      return false;
    }

    inputLine[len] = '\0';
    len = 0;

    return true;
  }

  // backspace
  if (ch == '\b' && len > 0)
  {
    len--;
    return false;
  }

  // abort
  if (ch == '\x03')
  {
    len = 0;
    return false;
  }

  // normal character
  inputLine[len] = ch;
  len++;
  return false;
}

int CLI::getCommand(char *command, float *params)
{
  // Copy command
  strncpy(command, strtok(CLI::inputLine, CLI::separator), MAX_LINE_LENGTH - 1);
  command[MAX_LINE_LENGTH - 1] = '\0';

  // Copy parameters
  int paramNum = 0;
  for (paramNum = 0; paramNum < MAX_PARAM_NUM; paramNum++)
  {
    char *buf = strtok(nullptr, CLI::separator);
    if (buf == nullptr)
    {
      break;
    }
    params[paramNum] = atof(buf);
  }

  // Reset input buffer
  len = 0;

  // Clear command available
  STATE_resetCmdAvailable(&state);

  return paramNum;
}
