#pragma once
#include "Constants.hpp"
#include "Solution.hpp"
#include "State.hpp"
#include <memory>

class StrategyContext
{
public:
  StrategyContext(std::shared_ptr<State> initialState);
  auto init() -> void;

  auto getInitialState() -> std::shared_ptr<State>;
  auto getGoalState() const -> State const&;

private:
  std::shared_ptr<State> initialState;
  State goalState;
};
