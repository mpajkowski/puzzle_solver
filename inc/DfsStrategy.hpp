#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"
#include "StrategyContext.hpp"

class DfsStrategy final : public Strategy
{
public:
  DfsStrategy(StrategyContext strategyContext, std::vector<State::Operator> const& order);
  auto findSolution() -> Solution override;

private:
  std::vector<State::Operator> order;
};
