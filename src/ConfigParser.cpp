#include "ConfigParser.hpp"
#include "State.hpp"
#include <stdexcept>
#include <unordered_set>

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
    cfg.strategyParam = parseHeuristic(*envIterator);
  } else {
    cfg.strategyParam = parseOrder(*envIterator);
  }

  ++envIterator;

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

auto ConfigParser::parseOrder(std::string const& env) -> std::vector<State::Operator>
{
  auto orderVec = std::vector<State::Operator>{};
  auto uniqueValidator = std::unordered_set<char>{};

  for (char ch : env) {
    if (uniqueValidator.find(ch) != std::end(uniqueValidator)) {
      throw std::invalid_argument{ "Typed same number twice" };
    }

    uniqueValidator.insert(ch);

    switch (ch) {
      case 'L':
        orderVec.push_back(State::Operator::Left);
        break;
      case 'R':
        orderVec.push_back(State::Operator::Right);
        break;
      case 'U':
        orderVec.push_back(State::Operator::Up);
        break;
      case 'D':
        orderVec.push_back(State::Operator::Down);
        break;
      default:
        throw std::invalid_argument{ "wrong char for move sequence" };
    }
  }
  return orderVec;
}
