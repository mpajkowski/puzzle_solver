#include "StateParser.hpp"
#include "State.hpp"
#include <exception>
#include <fstream>
#include <queue>
#include <sstream>

StateParser::StateParser(std::string const& firstStateFileName)
  : firstStateFileName{ firstStateFileName }
{}

auto StateParser::parse() -> std::shared_ptr<State>
{
  auto firstStateFile = std::fstream{ firstStateFileName };
  if (!firstStateFile.is_open()) {
    firstStateFile.open(firstStateFileName);
  }

  std::queue<std::string> rawLines;

  if (firstStateFile.is_open()) {
    for (std::string line; std::getline(firstStateFile, line);) {
      rawLines.push(line);
    }
  } else {
    throw std::logic_error{ "File not found" };
  }
  firstStateFile.close();

  auto numbers = std::queue<State::ValueType>{};

  while (!rawLines.empty()) {
    auto stream = std::stringstream{ rawLines.front() };

    // use int operator>> here - less pain
    for (int num; stream >> num;) {
      numbers.push(static_cast<State::ValueType>(num));
    }

    rawLines.pop();
  }

  State::ValueType row{ numbers.front() };
  numbers.pop();
  State::ValueType col{ numbers.front() };
  numbers.pop();

  std::vector<State::ValueType> board{};

  while (!numbers.empty()) {
    board.emplace_back(numbers.front());
    numbers.pop();
  }

  return std::make_shared<State>(row, col, board);
}
