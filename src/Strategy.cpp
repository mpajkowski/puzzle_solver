#include <Strategy.hpp>

Strategy::Strategy(StrategyContext strategyContext)
  : strategyContext{ std::move(strategyContext) }
{}
