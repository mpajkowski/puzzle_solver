#pragma once
#include "Strategy.hpp"

class BfsStrategy : public Strategy
{
public:
  BfsStrategy(State initialState, Constants::Order order);
  auto findSolution() -> Solution;

private:
  Constants::Order order;
};
