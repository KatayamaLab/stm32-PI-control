#ifndef _APP_HPP_
#define _APP_HPP_

#include "cli.hpp"
#include "code_def.h"
#include "measurement.hpp"
#include "state.h"
#include <cstring>

class App
{
public:
  static void main();
  static void SEND_DATA();
  static void PROCESS_COMMAND();
};

#endif