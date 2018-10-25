#pragma once
#include "Config.hpp"
#include "ResultsManager.hpp"
#include "Strategy.hpp"
#include "StrategyContext.hpp"
#include <memory>

class App
{
public:
  App(Config config);
  auto run() -> void;

private:
  auto init() -> void;
  std::unique_ptr<Strategy> strategy;
  std::unique_ptr<ResultsManager> resultsManager;
  Config config;
};
