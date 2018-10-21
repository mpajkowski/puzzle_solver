#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class State;

class StateParser
{
public:
  StateParser(std::string const& firstStateFilename);
  ~StateParser();
  auto parse() -> std::unique_ptr<State>;

private:
  std::string firstStateFileName;
  std::ifstream firstStateFile;
};
