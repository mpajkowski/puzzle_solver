#pragma once

#include "Config.hpp"
#include "Constants.hpp"
#include <string>
#include <vector>

class ConfigParser
{
public:
  ConfigParser(int argc, char** argv);
  Config createConfig();

private:
  auto parseStrategy(std::string const& env) -> Constants::Strategy;
  auto parseHeuristic(std::string const& env) -> Constants::Heuristic;
  auto parseOrder(std::string const& env) -> Constants::Order;
  std::vector<std::string> envs;
};
