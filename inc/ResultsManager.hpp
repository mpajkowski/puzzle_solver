#pragma once
#include "Config.hpp"
#include "Solution.hpp"

class ResultsManager
{
public:
  ResultsManager(Config const& config, Solution solution);
  auto saveData() -> void;

private:
  auto saveResult() -> void;
  auto saveMeta() -> void;

  Config config;
  Solution solution;
};
