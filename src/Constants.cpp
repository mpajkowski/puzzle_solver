#include "Constants.hpp"

const std::unordered_map<Constants::Strategy, std::string> Constants::strategy2string{
  { Constants::Strategy::BFS, "bfs" },
  { Constants::Strategy::DFS, "dfs" },
  { Constants::Strategy::ASTR, "astr" },
};

const std::unordered_map<Constants::Heuristic, std::string> Constants::heuristic2string{
  { Constants::Heuristic::HAMM, "hamm" },
  { Constants::Heuristic::MANH, "mahn" },
};

const std::unordered_map<Constants::Order, std::string> Constants::order2string{
  { Constants::Order::L_R_U_D, "LRUD" }, { Constants::Order::R_L_U_D, "RLUD" },
  { Constants::Order::U_L_R_D, "ULRD" }, { Constants::Order::L_U_R_D, "LURD" },
  { Constants::Order::R_U_L_D, "RULD" }, { Constants::Order::U_R_L_D, "URLD" },
  { Constants::Order::U_R_D_L, "URDL" }, { Constants::Order::R_U_D_L, "RUDL" },
  { Constants::Order::D_U_R_L, "DURL" }, { Constants::Order::U_D_R_L, "UDRL" },
  { Constants::Order::R_D_U_L, "RDUL" }, { Constants::Order::D_R_U_L, "DRUL" },
  { Constants::Order::D_L_U_R, "DLUR" }, { Constants::Order::L_D_U_R, "LDUR" },
  { Constants::Order::U_D_L_R, "UDLR" }, { Constants::Order::D_U_L_R, "DULR" },
  { Constants::Order::L_U_D_R, "LUDR" }, { Constants::Order::U_L_D_R, "ULDR" },
  { Constants::Order::R_L_D_U, "RLDU" }, { Constants::Order::L_R_D_U, "LRDU" },
  { Constants::Order::D_R_L_U, "DRLU" }, { Constants::Order::R_D_L_U, "RDLU" },
  { Constants::Order::L_D_R_U, "LDRU" }, { Constants::Order::D_L_R_U, "DLRU" },
};
