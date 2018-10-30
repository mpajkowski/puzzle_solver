#pragma once

#include <unordered_map>

namespace Constants {
enum class Strategy
{
  BFS,
  DFS,
  ASTR,
};

enum class Heuristic
{
  HAMM,
  MANH,
};

// TODO maybe map enum2string in a more fancy way?
extern const std::unordered_map<Strategy, std::string> strategy2string;
extern const std::unordered_map<Heuristic, std::string> heuristic2string;
}
