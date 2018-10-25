#pragma once
#include "Constants.hpp"
#include "Strategy.hpp"

class StrategyContext;

class AstrStrategy : public Strategy
{
public:
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;
};
