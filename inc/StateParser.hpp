#pragma once

#include <cstdint>
#include <memory>
#include <string>

class State;

class StateParser
{
public:
  StateParser(std::string const& firstStateFilename);
  auto parse() -> std::unique_ptr<State>;

private:
  std::string firstStateFileName;
};
