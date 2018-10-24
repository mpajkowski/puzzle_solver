#pragma once
#include "Config.hpp"
#include <memory>

class Strategy;
class ResultsManager;

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
