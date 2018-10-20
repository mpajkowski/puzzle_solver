#include "ConfigParser.hpp"
#include <stdexcept>

ConfigParser::ConfigParser(int argc, char** argv)
{
  for (int i = 0; i < argc; ++i) {
    envs.push_back(argv[i]);
  }
}

Config ConfigParser::createConfig()
{
  Config cfg;

  auto& strategyEnv = envs[1];
  cfg.strategy = parseStrategy(strategyEnv);
  return cfg;
}

Constants::Strategy parseStrategy(std::string const& env)
{
  for (const auto& it : Constants::strategy2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::logic_error { " Bad strategy variable " }
}
