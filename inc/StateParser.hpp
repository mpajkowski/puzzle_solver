#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

class State;

class StateParser
{
public:
  StateParser(std::string const& firstStateFilename);
  auto parse() -> State;

private:
  std::string firstStateFileName;
};
