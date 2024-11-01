#include "../include/Message_queue.hpp"

Message_queue::Message_queue()
    : dummy(std::make_unique<Node>()), head(dummy.get()), tail(dummy.get()) {}

void Message_queue::push(std::string message) {
  std::unique_ptr<Node> new_node = std::make_unique<Node>(message);
  Node *old_tail = tail.exchange(new_node.get());
  old_tail->next = std::move(new_node);
}

bool Message_queue::pop(std::string &message) {
  Node *old_head = head.load();
  Node *next = old_head->next.get();
  if (next) {
    message = next->message;
    head.store(next);
    return true;
  }
  return false;
}
