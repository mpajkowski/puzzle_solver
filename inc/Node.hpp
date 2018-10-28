#pragma once
#include "State.hpp"
#include <memory>

// FIXME create src/Node.cpp
class Node
{
public:
  Node(std::shared_ptr<Node> parent,
       std::shared_ptr<State> state,
       std::optional<State::Operator> op = std::nullopt)
    : parent{ parent }
    , state{ state }
    , op{ op }
  {}

  auto getParent() -> std::shared_ptr<Node> { return parent; }
  auto getState() -> std::shared_ptr<State>& { return state; }
  auto getOp() -> std::optional<State::Operator> { return op; }

private:
  std::shared_ptr<Node> parent;
  std::shared_ptr<State> state;
  std::optional<State::Operator> op;
};
