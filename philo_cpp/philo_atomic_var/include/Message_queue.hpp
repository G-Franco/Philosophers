#pragma once
#include "Message_node.hpp"

class Message_queue {
  private:
    std::unique_ptr<Node> dummy;
    std::atomic<Node *> head;
    std::atomic<Node *> tail;

  public:
    Message_queue();
    void push(std::string message);
    bool pop(std::string &message);
};
