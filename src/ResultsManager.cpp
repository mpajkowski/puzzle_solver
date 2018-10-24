#include "ResultsManager.hpp"

ResultsManager::ResultsManager(Config const& config, Solution solution)
  : config{ config }
  , solution{ std::move(solution) }
{}
