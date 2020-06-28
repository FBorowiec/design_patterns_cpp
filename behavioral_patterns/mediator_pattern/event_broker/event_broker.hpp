#ifndef BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_EVENT_BROKER_HPP
#define BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_EVENT_BROKER_HPP

#include <iostream>
#include <string>

#include <boost/signals2.hpp>

namespace behavioral {
namespace mediator_pattern {

struct EventData {
  virtual void Print() const = 0;
};

struct Player;

struct PlayerScoredData : EventData {
  PlayerScoredData(const std::string& player_name, const int goals_scored)
      : player_name_(player_name), goals_scored_(goals_scored) {}

  void Print() const override { std::cout << player_name_ << " has scored! (their " << goals_scored_ << " goal)\n"; }

  std::string player_name_;
  int goals_scored_;
};

struct Game {
  boost::signals2::signal<void(EventData*)> events_;
};

struct Player {
  Player(const std::string& name, Game& game) : name_(name), game_(game) {}

  void Score() {
    goals_scored_++;
    PlayerScoredData ps{name_, goals_scored_};
    game_.events_(&ps);
  }

  std::string name_;
  int goals_scored_{0};
  Game& game_;
};

struct Coach {
  Coach(Game& game) : game_(game) {
    game_.events_.connect([](EventData* e) {
      PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
      if (ps && ps->goals_scored_ < 3) {
        std::cout << "Coach says: well done, " << ps->player_name_ << "!\n";
      }
    });
  }

  Game& game_;
};

}  // namespace mediator_pattern
}  // namespace behavioral

#endif  // BEHAVIORAL_PATTERNS_MEDIATOR_PATTERN_EVENT_BROKER_HPP