#pragma once
#include "Constants.hpp"
#include "Strategy.hpp"

class StrategyContext;

class DfsStrategy : public Strategy
{
public:
  DfsStrategy(std::string const& order);
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;

private:
  std::string order;
};
