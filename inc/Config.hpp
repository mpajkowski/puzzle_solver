#pragma once

#include "Constants.hpp"
#include <variant>

struct Config
{
  Constants::Strategy strategy;
  std::variant<Constants::Order, Constants::Heuristic> orderOrHeuristic;

  std::string firstStateFileName;
  std::string solutionFileName;
  std::string additionalInfoFileName;
};