#pragma once
#include "Strategy.hpp"

class DfsStrategy : public Strategy
{
public:
  DfsStrategy(State initialState, Constants::Order order);
  auto findSolution() -> Solution;

private:
  Constants::Order order;
};
