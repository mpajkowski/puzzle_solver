#include <Node.hpp>

Node::Node(std::shared_ptr<State> state,
           std::shared_ptr<Node> parent,
           std::optional<State::Operator> op,
           std::uint8_t currentRecursionDepth)
  : state{ state }
  , parent{ parent }
  , op{ op }
  , currentRecursionDepth{ currentRecursionDepth }
{}

auto Node::getState() const -> std::shared_ptr<State>
{
  return state;
}

auto Node::getParent() const -> std::shared_ptr<Node>
{
  return parent;
}

auto Node::getCurrentRecursionDepth() const -> std::uint8_t
{
  return currentRecursionDepth;
}

auto Node::getOp() const -> std::optional<State::Operator>
{
  return op;
}
