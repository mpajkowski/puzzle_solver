#include "ConfigParser.hpp"
#include <iostream>

int main(int argc, char** argv)
{
  auto cp = ConfigParser(argc, argv);
  auto cfg = cp.createConfig();

  return 0;
}
