#pragma once

#include <cstdint>
#include <string>

class State;

class StateParser
{
public:
  StateParser(std::string const& firstStateFilename);
  auto parse() -> State;

private:
  std::string firstStateFileName;
};
