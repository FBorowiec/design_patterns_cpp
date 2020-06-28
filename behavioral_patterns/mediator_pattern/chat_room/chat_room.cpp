#include "chat_room.hpp"
#include "person.hpp"

namespace behavioral {
namespace mediator_pattern {

void ChatRoom::Broadcast(const std::string& origin, const std::string& message) {
  for (auto& p : people) {
    if (p->name_ != origin) {
      p->Receive(origin, message);
    }
  }
}

void ChatRoom::Join(Person* p) {
  std::string join_msg = p->name_ + " joined the chat.";
  Broadcast("room", join_msg);
  p->room_ = this;
  people.push_back(p);
}

}  // namespace mediator_pattern
}  // namespace behavioral
