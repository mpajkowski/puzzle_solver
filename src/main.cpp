#include "ConfigParser.hpp"
#include <iostream>

auto main(int argc, char** argv) -> int
{
  auto cp = ConfigParser{ argc, argv };
  auto cfg = cp.createConfig();

  return 0;
}
