#pragma once
#include "Constants.hpp"
#include "Strategy.hpp"

class StrategyContext;

class DfsStrategy : public Strategy
{
public:
  DfsStrategy(Constants::Order order);
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;

private:
  Constants::Order order;
};
