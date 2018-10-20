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

  if (cfg.strategy == Constants::Strategy::ASTR) {
    cfg.orderOrHeuristic = parseHeuristic(envs[2]);
  } else {
    cfg.orderOrHeuristic = parseOrder(envs[2]);
  }

  cfg.firstStateFileName = envs[4];
  cfg.solutionFileName = envs[5];
  cfg.additionalInfoFileName = envs[6];

  return cfg;
}

Constants::Strategy ConfigParser::parseStrategy(std::string const& env)
{
  for (const auto& it : Constants::strategy2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::logic_error{ " Bad strategy variable " };
}

Constants::Heuristic ConfigParser::parseHeuristic(std::string const& env)
{
  for (const auto& it : Constants::heuristic2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::logic_error{ " Bad heuristic variable " };
}

Constants::Order ConfigParser::parseOrder(std::string const& env)
{
  for (const auto& it : Constants::order2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::logic_error{ " Bad order variable " };
}
