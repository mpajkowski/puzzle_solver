#pragma once
#include "Strategy.hpp"

class BfsStrategy : public Strategy
{
public:
  BfsStrategy(State state, Constants::Order order);
  auto findSolution() -> Solution;

private:
  Constants::Order order;
};
