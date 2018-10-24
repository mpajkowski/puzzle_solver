#pragma once
#include "Config.hpp"
#include "Solution.hpp"

class ResultsManager
{
public:
  ResultsManager(Config const& config, Solution solution);

private:
  Config config;
  Solution solution;
};
