#include "ResultsManager.hpp"
#include <fstream>
#include <iostream>

ResultsManager::ResultsManager(Config const& config, Solution solution)
  : config{ config }
  , solution{ std::move(solution) }
{}

auto ResultsManager::saveData() -> void
{
  // FIXME save to file, not to stdout
  if (solution.operators) {
    auto opStr = solution.operators.value();
    std::cout << "PATH: " << opStr << ", length: " << opStr.size() << "\n";
  } else {
    std::cout << "PATH NOT FOUND\n";
  }

  std::cout << "VISITED STATES COUNT: " << solution.visitedStatesCount << "\n";
  std::cout << "PROCESSED STATES COUNT: " << solution.processedStatesCount << "\n";
  std::cout << "MAX RECURSION DEPTH: " << solution.maxRecursionDepth << "\n";
  std::cout << "TIME: " << solution.duration.count() << "ms" << std::endl;

  saveResult();
  saveMeta();
}

auto ResultsManager::saveResult() -> void
{
  auto file = std::ofstream{ config.solutionFileName };

  if (!solution.operators) {
    file << "-1";
  } else {
    auto opStr = solution.operators.value();
    file << opStr.size() << '\n';
    file << opStr;
  }

  file.close();
}

auto ResultsManager::saveMeta() -> void {}
