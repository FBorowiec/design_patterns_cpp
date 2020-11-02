/**
 * Getting notification when things happen.
 * MOTIVATION:
 * We need to be informed when certain things happen:
 *  - Object's field changes
 *  - Object does something
 *  - Some external event occurs
 * We want to listen to events and notified when they occur:
 * Terminology:
 *  - event and subscriber
 *  - signal and slots
 *
 * An observer is an object that wishes to be informed about events happening in the system.
 * The entity generating the events is an observable.
 * Observale implementation is always intrusive (observer doesn't need to be).
 * Multithreaded/reentrant use can cause issues.
 */
#include <iostream>
#include <string>
#include <vector>

namespace behavioral {
namespace observer_pattern {

template <typename>
class Observer;

template <typename T>
class Observable {
 public:
  void Notify(T& source, const std::string& field_name) {
    for (auto o : observers) {
      o->FieldChange(source, field_name);
    }
  }

  void Subscribe(Observer<T>& observer) { observers.push_back(&observer); }

  void Unsubscribe(Observer<T>& observer) {
    observers.erase(remove(observers.begin(), observers.end(), &observer), observers.end());
  }

  std::vector<Observer<T>*> observers;
};

class Person : public Observable<Person> {
 public:
  Person(int age) : age_(age) {}

  void SetAge(int age) {
    if (this->age_ == age) return;
    this->age_ = age;
    Notify(*this, "age");
  }

  int GetAge() { return age_; }

 private:
  int age_;
};

// observer & observable
template <typename T>
class Observer {
 public:
  virtual void FieldChange(T& source, const std::string& field_name) = 0;
};

struct ConsolePersonObserver : public Observer<Person> {
  virtual void FieldChange(Person& source, const std::string& field_name) override {
    std::cout << "Person's " << field_name << " has changed to";
    if (field_name == "age") std::cout << source.GetAge() << std::endl;
  }
};

}  // namespace observer_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::observer_pattern;

TEST(ObserverPatternTest, UsageOfTheObserverPattern) {
  Person person{10};
  ConsolePersonObserver cpo;
  person.Subscribe(cpo);

  person.SetAge(11);
  person.SetAge(12);

  person.Unsubscribe(cpo);
  person.SetAge(13);
}

}  // namespace
