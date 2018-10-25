#include "App.hpp"
#include "AstrStrategy.hpp"
#include "BfsStrategy.hpp"
#include "DfsStrategy.hpp"
#include "ResultsManager.hpp"
#include "State.hpp"
#include "StateParser.hpp"
#include "Strategy.hpp"
#include "StrategyContext.hpp"

App::App(Config cfg)
  : config{ std::move(cfg) }
  , strategy{ nullptr }
  , resultsManager{ nullptr }
{
  init();
}

auto App::run() -> void
{
  auto stateParser = StateParser{ config.firstStateFileName };
  auto initialState = stateParser.parse();
  auto strategyContext = StrategyContext{ initialState };

  auto solution = strategy->findSolution(std::move(strategyContext));

  // dispatch solution to ResultsManager
  resultsManager = std::make_unique<ResultsManager>(config, std::move(solution));
}

auto App::init() -> void
{
  switch (config.strategy) {
    case Constants::Strategy::BFS:
      strategy = std::make_unique<BfsStrategy>(std::get<Constants::Order>(config.strategyParam));
      break;
    case Constants::Strategy::DFS:
      strategy = std::make_unique<DfsStrategy>(std::get<Constants::Order>(config.strategyParam));
      break;
    case Constants::Strategy::ASTR:
      strategy = std::make_unique<AstrStrategy>();
      break;
  }
}
