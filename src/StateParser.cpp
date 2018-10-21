#include "StateParser.hpp"
#include "State.hpp"
#include <exception>

StateParser::StateParser(std::string const& firstStateFileName)
  : firstStateFileName{ firstStateFileName }
  , firstStateFile{}
{}

StateParser::~StateParser()
{
  if (!firstStateFile.is_open()) {
    firstStateFile.close();
  }
}

// TODO parse puzzle file
auto StateParser::parse() -> std::unique_ptr<State>
{
  if (!firstStateFile.is_open()) {
    firstStateFile.open(firstStateFileName);
  }

  auto sequence = std::vector<std::uint8_t>(16);
  return {};
}
