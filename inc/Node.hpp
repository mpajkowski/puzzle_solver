#pragma once
#include "State.hpp"
#include <memory>

template<typename T>
class Node
{
public:
  Node(std::shared_ptr<State> state, T payload = T{});

  Node(Node const&) = default;
  Node(Node&&) = default;

  Node& operator=(Node const&) = default;
  Node& operator=(Node&&) = default;

  auto getState() -> std::shared_ptr<State>;
  auto getPayload() -> T;

private:
  std::shared_ptr<State> state;
  T payload;
};

template<typename T>
Node<T>::Node(std::shared_ptr<State> state, T payload)
  : state{ state }
  , payload{ payload }
{}

template<typename T>
auto Node<T>::getState() -> std::shared_ptr<State>
{
  return state;
}

template<typename T>
auto Node<T>::getPayload() -> T
{
  return payload;
}
