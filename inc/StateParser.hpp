#pragma once

#include <cstdint>
#include <memory>
#include <string>

class State;

class StateParser
{
public:
  StateParser(std::string const& firstStateFilename);
  auto parse() -> std::shared_ptr<State>;

private:
  std::string firstStateFileName;
};
