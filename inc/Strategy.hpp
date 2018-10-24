#pragma once
#include "Constants.hpp"
#include "Solution.hpp"
#include "State.hpp"

class State;

class Strategy
{
public:
  Strategy(State state);
  virtual auto findSolution() -> Solution;

  virtual ~Strategy() = default;

protected:
  auto getState() -> State&;

private:
  State state;
};
