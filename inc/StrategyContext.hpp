#pragma once
#include "Constants.hpp"
#include "Solution.hpp"
#include "State.hpp"

class State;

class StrategyContext
{
public:
  StrategyContext(State initialState);
  auto init() -> void;

  auto getOperatedState() -> State&;
  auto getWantedState() const -> State const&;

private:
  State operatedState;
  State wantedState;
};
