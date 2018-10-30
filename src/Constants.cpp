#include "Constants.hpp"

const std::unordered_map<Constants::Strategy, std::string> Constants::strategy2string{
  { Constants::Strategy::BFS, "bfs" },
  { Constants::Strategy::DFS, "dfs" },
  { Constants::Strategy::ASTR, "astr" },
};

const std::unordered_map<Constants::Heuristic, std::string> Constants::heuristic2string{
  { Constants::Heuristic::HAMM, "hamm" },
  { Constants::Heuristic::MANH, "manh" },
};
