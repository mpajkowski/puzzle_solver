#include "App.hpp"
#include "AstrStrategy.hpp"
#include "BfsStrategy.hpp"
#include "DfsStrategy.hpp"
#include "State.hpp"
#include "StateParser.hpp"
#include "Strategy.hpp"

App::App(Config cfg)
  : config{ std::move(cfg) }
  , strategy{ nullptr }
{
  init();
}

auto App::run() -> void
{
  auto solution = strategy->findSolution();
}

auto App::init() -> void
{
  auto stateParser = StateParser{ config.firstStateFileName };
  auto state = stateParser.parse();

  switch (config.strategy) {
    case Constants::Strategy::BFS:
      strategy = std::make_unique<BfsStrategy>(std::move(state));
      break;
    case Constants::Strategy::DFS:
      strategy = std::make_unique<DfsStrategy>(std::move(state));
      break;
    case Constants::Strategy::ASTR:
      strategy = std::make_unique<AstrStrategy>(std::move(state));
      break;
  }

  // TODO finish...
}
