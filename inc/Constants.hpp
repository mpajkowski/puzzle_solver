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

enum class Order
{
  L_R_U_D,
  R_L_U_D,
  U_L_R_D,
  L_U_R_D,
  R_U_L_D,
  U_R_L_D,
  U_R_D_L,
  R_U_D_L,
  D_U_R_L,
  U_D_R_L,
  R_D_U_L,
  D_R_U_L,
  D_L_U_R,
  L_D_U_R,
  U_D_L_R,
  D_U_L_R,
  L_U_D_R,
  U_L_D_R,
  R_L_D_U,
  L_R_D_U,
  D_R_L_U,
  R_D_L_U,
  L_D_R_U,
  D_L_R_U,
};

extern const std::unordered_map<Strategy, std::string> strategy2string;
extern const std::unordered_map<Heuristic, std::string> heuristic2string;
extern const std::unordered_map<Order, std::string> order2string;

}
