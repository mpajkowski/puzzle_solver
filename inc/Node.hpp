#pragma once
#include "State.hpp"
#include <memory>

class Node
{
public:
  Node(std::shared_ptr<Node> parent,
       std::shared_ptr<State> state,
       std::optional<State::Operator> op = std::nullopt);

  auto getParent() -> std::shared_ptr<Node>;
  auto getState() -> std::shared_ptr<State>&;
  auto getOp() -> std::optional<State::Operator>;

private:
  std::shared_ptr<Node> parent;
  std::shared_ptr<State> state;
  std::optional<State::Operator> op;
};
