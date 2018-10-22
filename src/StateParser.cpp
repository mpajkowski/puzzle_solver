#include "StateParser.hpp"
#include "State.hpp"
#include <exception>
#include <iostream>
#include <queue>
#include <sstream>

StateParser::StateParser(std::string const& firstStateFileName)
  : firstStateFileName{ firstStateFileName }
{}

auto StateParser::parse() -> std::unique_ptr<State>
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
    throw std::logic_error{ "IO Exception" };
  }
  firstStateFile.close();

  std::cout << rawLines.size() << " MAMEEEE" << std::endl;

  auto numbers = std::queue<std::uint8_t>{};

  while (!rawLines.empty()) {
    auto stream = std::stringstream{ rawLines.front() };

    // use int operator>> here - less pain
    for (int num; stream >> num;) {
      numbers.push(static_cast<std::uint8_t>(num));
    }

    rawLines.pop();
  }

  std::uint8_t row{ numbers.front() };
  numbers.pop();
  std::uint8_t col{ numbers.front() };
  numbers.pop();

  std::vector<uint8_t> board{};

  while (!numbers.empty()) {
    board.emplace_back(numbers.front());
    numbers.pop();
  }

  auto state = std::make_unique<State>();

  state->board = std::move(board);
  state->col = col;
  state->row = row;

  for (auto x : state->board) {
    std::cout << +x << " ";
  }
  return state;
}
