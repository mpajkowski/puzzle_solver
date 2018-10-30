#include "ResultsManager.hpp"
#include <iostream>

ResultsManager::ResultsManager(Config const& config, Solution solution)
  : config{ config }
  , solution{ std::move(solution) }
{}

auto ResultsManager::saveData() -> void
{
  // FIXME save to file, not to stdout
  std::cout << "PATH: " << solution.operators << ", length: " << solution.operators.size() << "\n";
  std::cout << "VISITED STATES COUNT: " << solution.visitedStatesCount << "\n";
  std::cout << "PROCESSED STATES COUNT: " << solution.processedStatesCount << "\n";
  std::cout << "MAX RECURSION DEPTH: " << solution.maxRecursionDepth << "\n";
  std::cout << "TIME: " << solution.duration.count() << std::endl;
}
