#include "Node.hpp"

Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<State> state, std::optional<State::Operator> op)
  : parent{ parent }
  , state{ state }
  , op{ op }
{}

auto Node::getParent() -> std::shared_ptr<Node>
{
  return parent;
}

auto Node::getState() -> std::shared_ptr<State>&
{
  return state;
}

auto Node::getOp() -> std::optional<State::Operator>
{
  return op;
}
