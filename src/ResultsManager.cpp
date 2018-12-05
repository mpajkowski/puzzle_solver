#include "ResultsManager.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

ResultsManager::ResultsManager(Config const& config, Solution solution)
  : config{ config }
  , solution{ std::move(solution) }
{}

auto ResultsManager::saveData() -> void
{
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
  file << std::endl;

  file.close();
}

auto ResultsManager::saveMeta() -> void
{
  auto file = std::ofstream{ config.additionalInfoFileName };
  auto opStr = solution.operators;

  file << (opStr.has_value() ? opStr.value().size() : -1) << '\n';
  file << solution.visitedStatesCount << '\n';
  file << solution.processedStatesCount << '\n';
  file << solution.maxRecursionDepth << '\n';
  file << std::setprecision(3) << std::fixed << solution.duration.count();
  file << std::endl;

  file.close();
}
