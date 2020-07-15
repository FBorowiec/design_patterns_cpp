#include <iostream>
#include <map>
#include <sstream>
#include <typeindex>

namespace behavioral {
namespace visitor_pattern {

struct GameObject;
void Collide(GameObject& first, GameObject& second);

struct GameObject {
 public:
  virtual ~GameObject() = default;
  virtual std::type_index type() const = 0;
  virtual void Collide(GameObject& other) { behavioral::visitor_pattern::Collide(*this, other); }
};

// CRTP
template <typename T>
struct GameObjectImpl : public GameObject {
 public:
  std::type_index type() const override { return typeid(T); }
};

struct Planet : public GameObjectImpl<Planet> {};
struct Asteroid : public GameObjectImpl<Asteroid> {};
struct Spaceship : public GameObjectImpl<Spaceship> {};

void SpaceshipPlanet() { std::cout << "Spaceship lands on a planet\n"; }
void AsteroidPlanet() { std::cout << "Asteroid burns up in the atmosphere\n"; }
void AsteroidSpaceship() { std::cout << "Asteroid hits and destroys spaceship\n"; }

std::map<std::pair<std::type_index, std::type_index>, void (*)(void)> outcomes{
    {{typeid(Spaceship), typeid(Planet)}, SpaceshipPlanet},
    {{typeid(Asteroid), typeid(Planet)}, AsteroidPlanet},
    {{typeid(Asteroid), typeid(Spaceship)}, AsteroidSpaceship}};

void Collide(GameObject& first, GameObject& second) {
  auto it = outcomes.find({first.type(), second.type()});
  if (it == outcomes.end()) {
    it = outcomes.find({second.type(), first.type()});
    if (it == outcomes.end()) {
      std::cout << "Objects pass each other harmlessly\n";
      return;
    }
  }
  it->second();
}

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheMultimethods) {
  Asteroid asteroid;
  Planet planet;
  Spaceship spaceship;

  Collide(planet, spaceship);
  Collide(planet, asteroid);
  Collide(spaceship, asteroid);
  Collide(planet, planet);
}

}  // namespace
