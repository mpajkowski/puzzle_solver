#pragma once
#include "Constants.hpp"
#include "Strategy.hpp"

class StrategyContext;

class BfsStrategy : public Strategy
{
public:
  BfsStrategy(Constants::Order order);
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;

private:
  Constants::Order order;
};
