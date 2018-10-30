#include "Config.hpp"
#include <sstream>

auto Config::toString() const -> std::string
{
  auto os = std::ostringstream{};

  os << "Strategy: " << Constants::strategy2string.at(strategy) << "\n";

  // TODO FIXME
  // if (std::holds_alternative<std::string>(strategyParam)) {
  //   os << "Order: " << std::get<std::string>(strategyParam);
  // } else {
  //   os << "Heuristic: " << Constants::heuristic2string.at(std::get<Constants::Heuristic>(strategyParam));
  // }

  os << "First state file name: " << firstStateFileName;
  os << "Solution file name: " << solutionFileName;
  os << "Additional info file name: " << additionalInfoFileName;

  return os.str();
}
