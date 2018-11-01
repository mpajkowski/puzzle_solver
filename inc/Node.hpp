#pragma once
#include "State.hpp"
#include <memory>

template<typename T>
class Node
{
public:
  Node(std::shared_ptr<Node> parent, std::shared_ptr<State> state, T op, std::uint8_t recursionDepth = 0u);
  Node(Node const&) = default;

  auto getParent() -> std::shared_ptr<Node>;
  auto getState() -> std::shared_ptr<State>&;
  auto getOp() -> T;
  auto getRecursionDepth() -> std::uint8_t;

private:
  std::shared_ptr<Node> parent;
  std::shared_ptr<State> state;
  T op;
  std::size_t recursionDepth;
};

template<typename T>
Node<T>::Node(std::shared_ptr<Node> parent, std::shared_ptr<State> state, T op, std::uint8_t recursionDepth)
  : parent{ parent }
  , state{ state }
  , op{ op }
  , recursionDepth{ recursionDepth }
{}

template<typename T>
auto Node<T>::getParent() -> std::shared_ptr<Node>
{
  return parent;
}

template<typename T>
auto Node<T>::getState() -> std::shared_ptr<State>&
{
  return state;
}

template<typename T>
auto Node<T>::getOp() -> T
{
  return op;
}

template<typename T>
auto Node<T>::getRecursionDepth() -> std::uint8_t
{
  return recursionDepth;
}
