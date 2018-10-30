#include "App.hpp"
#include "ConfigParser.hpp"
#include "State.hpp"
#include "StateParser.hpp"
#include <iostream>

auto main(int argc, char** argv) -> int
{
  auto cp = ConfigParser{ argc, argv };
  auto cfg = cp.createConfig();
  auto app = App{ cfg };
  app.run();

  return 0;
}
