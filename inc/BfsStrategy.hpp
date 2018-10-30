#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"

class StrategyContext;

class BfsStrategy : public Strategy
{
public:
  BfsStrategy(std::vector<State::Operator> const& order);
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;

private:
  auto init() -> void;
  std::vector<State::Operator> order;
};
