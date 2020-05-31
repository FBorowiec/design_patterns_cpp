/**
 * Sequence of handlers processing an event one after another.
 * MOTIVATION:
 * CoR can be implemented as:
 *  - A chain of pointers/references (singly linked list)
 *  - Centralized list
 * Enlist objects in the chain, possibly controlling their order
 * Object removeal from chain (e.g., disconnect from a signal)
 */
#include <memory>
#include <ostream>
#include <string>

namespace behavioral {
namespace chain_of_responsibility_pattern {

/**
 * Pointer chain
 */
struct Creature {
 public:
  Creature(std::string name, int attack, int defence) : name_(name), attack_(attack), defence_(defence) {}

  friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
    os << "Name: " << obj.name_ << ", Attack: " << obj.attack_ << ", Defence: " << obj.defence_;
    return os;
  }

 public:  // should define setters, getters
  std::string name_;
  int attack_, defence_;
};

class CreatureModifier {
 public:
  CreatureModifier(Creature& creature) : creature_(creature) {}

  void Add(CreatureModifier* cm) {
    if (next)
      next->Add(cm);
    else
      next = cm;
  }

  virtual void Handle() {
    if (next) next->Handle();
  }

 protected:
  Creature& creature_;

 private:
  CreatureModifier* next = nullptr;
};

class DoubleAttackModifier : public CreatureModifier {
 public:
  DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {}

  void Handle() override {
    creature_.attack_ *= 2;
    CreatureModifier::Handle();
  }
};

class IncreaseDefenceModifier : public CreatureModifier {
 public:
  IncreaseDefenceModifier(Creature& creature) : CreatureModifier(creature) {}

  void Handle() override {
    if (creature_.attack_ <= 2) creature_.defence_++;
    CreatureModifier::Handle();
  }
};

class NoBonusesModifier : public CreatureModifier {
 public:
  NoBonusesModifier(Creature& creature) : CreatureModifier(creature) {}

  void Handle() override {}
};

}  // namespace chain_of_responsibility_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::chain_of_responsibility_pattern;

TEST(ChainOfResponsibilityPatternTest, UsageOfTheChainOfResponsibilityPattern) {
  Creature goblin{"Goblin", 1, 1};

  CreatureModifier root{goblin};
  DoubleAttackModifier r1{goblin};
  DoubleAttackModifier r1_2{goblin};
  IncreaseDefenceModifier r2{goblin};

  root.Add(&r1);
  root.Add(&r1_2);  // a = 4
  root.Add(&r2);    // no-op

  root.Handle();

  std::cout << goblin << std::endl;
}

/**
 * How to disable the chain of responsibility?
 */
TEST(ChainOfResponsibilityPatternTest, CancellingTheChainOfResponsibilityPattern) {
  Creature goblin{"Goblin", 1, 1};

  CreatureModifier root{goblin};
  DoubleAttackModifier r1{goblin};
  DoubleAttackModifier r1_2{goblin};
  IncreaseDefenceModifier r2{goblin};

  NoBonusesModifier curse{goblin};  // cancelling the chain of responsibility
  root.Add(&curse);

  root.Add(&r1);
  root.Add(&r1_2);  // a = 1!
  root.Add(&r2);    // no-op

  root.Handle();

  std::cout << goblin << std::endl;
}

}  // namespace
