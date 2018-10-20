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
  Constants::Strategy parseStrategy(std::string const& env);
  Constants::Heuristic parseHeuristic(std::string const& env);
  Constants::Order parseOrder(std::string const& env);
  std::vector<std::string> envs;
};
