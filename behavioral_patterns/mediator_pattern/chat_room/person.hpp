#ifndef BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_PERSON_HPP
#define BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_PERSON_HPP

#include <string>
#include <vector>

namespace behavioral {
namespace mediator_pattern {

struct ChatRoom;

struct Person {
  Person(const std::string& name);

  void Say(const std::string& message) const;
  void Pm(const std::string& who, const std::string& message) const;
  void Receive(const std::string& origin, const std::string& message);

  bool operator==(const Person& rhs) const;

  ChatRoom* room_{nullptr};
  std::string name_;
  std::vector<std::string> chat_log_;
};

}  // namespace mediator_pattern
}  // namespace behavioral

#endif  // BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_PERSON_HPP