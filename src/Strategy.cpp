#include "Strategy.hpp"
#include "State.hpp"

Strategy::Strategy(State state)
  : state{ std::move(state) }
{}

auto Strategy::getState() -> State&
{
  return state;
}
