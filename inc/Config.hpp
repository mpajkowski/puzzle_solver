#pragma once

#include "Constants.hpp"
#include <variant>

struct Config
{
  auto toString() const -> std::string;

  Constants::Strategy strategy;
  std::variant<std::string, Constants::Heuristic> strategyParam;

  std::string firstStateFileName;
  std::string solutionFileName;
  std::string additionalInfoFileName;
};
