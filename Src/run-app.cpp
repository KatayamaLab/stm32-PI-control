#include "app.hpp"

// Interface to C++ program
extern "C" void runApp()
{

  CLI::println("hello :)");

  STATE_init(&state, Mmt::dataBuffer, Mmt::pwmBuffer);

  while (1)
  {
    App::main();
  }
}