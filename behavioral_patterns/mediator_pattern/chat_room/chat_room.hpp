#ifndef BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_CHAT_ROOM_HPP
#define BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_CHAT_ROOM_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "person.hpp"

namespace behavioral {
namespace mediator_pattern {

struct ChatRoom {
  void Broadcast(const std::string& origin, const std::string& message);
  void Join(Person* p);
  void Message(const std::string& origin, const std::string& who, const std::string& message) {
    auto target = std::find_if(std::begin(people), std::end(people), [&](const Person* p) { return p->name_ == who; });
    if (target != std::end(people)) {
      (*target)->Receive(origin, message);
    }
  }

  std::vector<Person*> people;
};

}  // namespace mediator_pattern
}  // namespace behavioral

#endif  // BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_CHAT_ROOM_HPP