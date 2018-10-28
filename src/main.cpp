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
  std::cout << sizeof(State) << std::endl;
  std::cout << sizeof(std::vector<uint8_t>) << std::endl;
  std::cout << sizeof(uint8_t);

  return 0;
}
