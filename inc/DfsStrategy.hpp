#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"

class StrategyContext;

class DfsStrategy : public Strategy
{
public:
  DfsStrategy(std::vector<State::Operator> const& order);
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;

private:
  std::vector<State::Operator> order;
};
