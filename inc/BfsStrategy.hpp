#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"

class StrategyContext;

class BfsStrategy final : public Strategy
{
public:
  BfsStrategy(StrategyContext strategyContext, std::vector<State::Operator> const& order);
  auto findSolution() -> Solution override;

private:
  std::vector<State::Operator> order;
};
