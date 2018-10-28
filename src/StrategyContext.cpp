#include "StrategyContext.hpp"
#include "State.hpp"
#include <numeric>

StrategyContext::StrategyContext(std::shared_ptr<State> initialState)
  : initialState{ initialState }
  , goalState{ 1, 1, { 0 } }
{
  init();
}

auto StrategyContext::init() -> void
{
  auto board = std::vector<std::uint8_t>(initialState->getRow() * initialState->getCol());
  std::iota(std::begin(board), std::end(board) - 1, 1);
  board.back() = 0;
  goalState = State{ initialState->getRow(), initialState->getCol(), std::move(board) };
}

auto StrategyContext::getInitialState() -> std::shared_ptr<State>
{
  return initialState;
}

auto StrategyContext::getGoalState() const -> State const&
{
  return goalState;
}
