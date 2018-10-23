#include "Strategy.hpp"
#include "State.hpp"

Strategy::Strategy(std::unique_ptr<State> state)
  : state{ std::move(state) }
{}
