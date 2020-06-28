#include <iostream>

#include "chat_room.hpp"
#include "person.hpp"

namespace behavioral {
namespace mediator_pattern {

Person::Person(const std::string& name) : name_(name) {}

void Person::Say(const std::string& message) const { room_->Broadcast(name_, message); }

void Person::Pm(const std::string& who, const std::string& message) const { room_->Message(name_, who, message); }

void Person::Receive(const std::string& origin, const std::string& message) {
  std::string s{origin + ": \"" + message + "\""};
  std::cout << "[" << name_ << "'s chat session]" << s << "\n";
  chat_log_.emplace_back(s);
}

bool Person::operator==(const Person& rhs) const { return name_ == rhs.name_; }

}  // namespace mediator_pattern
}  // namespace behavioral
