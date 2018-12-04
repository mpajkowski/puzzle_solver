#pragma once
#include "State.hpp"
#include <memory>

class Node
{
public:
  Node(std::shared_ptr<State> state,
       std::shared_ptr<Node> parent = nullptr,
       std::optional<State::Operator> op = std::nullopt,
       std::uint8_t currentRecursionDepth = 0);

  Node(Node const&) = default;
  Node(Node&&) = default;

  Node& operator=(Node const&) = default;
  Node& operator=(Node&&) = default;

  auto getState() const -> std::shared_ptr<State>;
  auto getParent() const -> std::shared_ptr<Node>;
  auto getCurrentRecursionDepth() const -> std::uint8_t;
  auto getOp() const -> std::optional<State::Operator>;

private:
  std::shared_ptr<State> state;
  std::shared_ptr<Node> parent;
  std::optional<State::Operator> op;
  std::uint8_t currentRecursionDepth;
};

