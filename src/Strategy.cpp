#include "Strategy.hpp"
#include "State.hpp"
#include <numeric>

Strategy::Strategy(State inputState)
  : operatedState{ std::move(inputState) }
  , wantedState{ 1, 1, { 0 } }
{
  init();
}

auto Strategy::init() -> void
{
  auto wantedBoard = std::vector<std::uint8_t>(operatedState.getRow() * operatedState.getCol());
  std::iota(std::begin(wantedBoard), std::end(wantedBoard) - 1, 1);
  wantedBoard.back() = 0;
  wantedState = State{ operatedState.getRow(), operatedState.getCol(), std::move(wantedBoard) };
}

auto Strategy::getOperatedState() -> State&
{
  return operatedState;
}

auto Strategy::getWantedState() const -> State const&
{
  return wantedState;
}
