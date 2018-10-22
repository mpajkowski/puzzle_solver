#include "ConfigParser.hpp"
#include "State.hpp"
#include "StateParser.hpp"
#include <iostream>

auto main(int argc, char** argv) -> int
{
  auto cp = ConfigParser{ argc, argv };
  auto cfg = cp.createConfig();
  auto stateParser = StateParser{ cfg.firstStateFileName };
  auto test = stateParser.parse();

  return 0;
}
