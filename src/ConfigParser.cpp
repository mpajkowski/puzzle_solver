#include "ConfigParser.hpp"
#include <stdexcept>

ConfigParser::ConfigParser(int argc, char** argv)
{
  for (int i = 0; i < argc; ++i) {
    envs.push_back(argv[i]);
  }
}

auto ConfigParser::createConfig() -> Config
{
  auto cfg = Config{};
  auto envIterator = ++std::begin(envs);

  cfg.strategy = parseStrategy(*envIterator++);

  if (cfg.strategy == Constants::Strategy::ASTR) {
    cfg.strategyParam = parseHeuristic(*envIterator++);
  } else {
    cfg.strategyParam = parseOrder(*envIterator++);
  }

  cfg.firstStateFileName = *envIterator++;
  cfg.solutionFileName = *envIterator++;
  cfg.additionalInfoFileName = *envIterator++;

  return cfg;
}

auto ConfigParser::parseStrategy(std::string const& env) -> Constants::Strategy
{
  for (auto const& it : Constants::strategy2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::invalid_argument{ "Bad strategy variable" };
}

auto ConfigParser::parseHeuristic(std::string const& env) -> Constants::Heuristic
{
  for (auto const& it : Constants::heuristic2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::invalid_argument{ "Bad heuristic variable" };
}

auto ConfigParser::parseOrder(std::string const& env) -> Constants::Order
{
  for (auto const& it : Constants::order2string) {
    if (it.second == env) {
      return it.first;
    }
  }

  throw std::invalid_argument{ "Bad order variable" };
}
