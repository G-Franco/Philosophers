#pragma once
#include <atomic>
#include <iostream>
#include <memory>

struct Node {
  std::string message;
  std::unique_ptr<Node> next;

  Node() : message(), next(nullptr) {}
  Node(std::string message) : message(message), next(nullptr) {}
};
