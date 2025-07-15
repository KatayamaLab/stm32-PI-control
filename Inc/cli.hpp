#ifndef _CLI_HPP_
#define _CLI_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>

#include "const.h"
#include "drivers.hpp"
#include "state.h"

class CLI
{
private:
  static constexpr const char *separator = " ";
  static char *itoa(int val, char *buf);
  static char *itoa(uint32_t val, char *buf);
  static float atof(const char *buf);

public:
  static uint8_t len;
  static char inputLine[MAX_LINE_LENGTH];

public:
  static bool getLine(char ch);
  static int getCommand(char *command, float *params);
  // Print functions
  static void print(const char *);
  static void print(const int);
  static void print(uint32_t);

  static void println(const char *);
  static void println(const int);
  static void println(uint32_t);

  static void printState(State *state);
};

#endif