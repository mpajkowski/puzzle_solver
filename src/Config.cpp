#include "Config.hpp"
#include <sstream>

auto Config::toString() const -> std::string
{
  auto os = std::ostringstream{};

  os << "Strategy: " << Constants::strategy2string.at(strategy) << '\n';

  if (std::holds_alternative<std::vector<State::Operator>>(strategyParam)) {
    os << "Order: ";

    for (auto dir : std::get<std::vector<State::Operator>>(strategyParam)) {
      os << static_cast<std::underlying_type<State::Operator>::type>(dir);
    }

    os << '\n';
  } else {
    os << "Heuristic: " << Constants::heuristic2string.at(std::get<Constants::Heuristic>(strategyParam))
       << '\n';
  }

  os << "First state file name: " << firstStateFileName;
  os << "Solution file name: " << solutionFileName;
  os << "Additional info file name: " << additionalInfoFileName;

  return os.str();
}
