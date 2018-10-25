#pragma once
#include "Constants.hpp"
#include "Solution.hpp"
#include "State.hpp"

class State;

class Strategy
{
public:
  Strategy(State initialState);
  virtual auto findSolution() -> Solution = 0;

  virtual ~Strategy() = default;

  auto init() -> void;

protected:
  auto getOperatedState() -> State&;
  auto getWantedState() const -> State const&;

private:
  State operatedState;
  State wantedState;
};
