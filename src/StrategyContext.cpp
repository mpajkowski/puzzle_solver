#include "StrategyContext.hpp"
#include "State.hpp"
#include <numeric>

StrategyContext::StrategyContext(State initialState)
  : operatedState{ std::move(initialState) }
  , wantedState{ 1, 1, { 0 } }
{
  init();
}

auto StrategyContext::init() -> void
{
  auto wantedBoard = std::vector<std::uint8_t>(operatedState.getRow() * operatedState.getCol());
  std::iota(std::begin(wantedBoard), std::end(wantedBoard) - 1, 1);
  wantedBoard.back() = 0;
  wantedState = State{ operatedState.getRow(), operatedState.getCol(), std::move(wantedBoard) };
}

auto StrategyContext::getOperatedState() -> State&
{
  return operatedState;
}

auto StrategyContext::getWantedState() const -> State const&
{
  return wantedState;
}
