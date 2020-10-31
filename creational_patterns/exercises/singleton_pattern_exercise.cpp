/**
 * Implementing a singleton is very easy.
 * You are given the function SingletonTester::is_singleton().
 * This function takes a factory and needs to return true or false depending on whether that factory produces
 * singletons. What traits do two 'instances' of a singleton have in common.
 */
#include <functional>

namespace creational {
namespace singleton_pattern_exercise {

struct SingletonTester {
  template <typename T>
  bool is_singleton(std::function<T*()> factory) {
    T* _1 = factory();
    T* _2 = factory();
    return _1 == _2;
  }
};

}  // namespace singleton_pattern_exercise
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace creational::singleton_pattern_exercise;

TEST(SingletonTesterTest, SimpleTest) {
  SingletonTester tester;
  ASSERT_TRUE(tester.is_singleton<SingletonTester>([&]() -> SingletonTester* { return &tester; }))
      << "Expected a singleton in this case; provided lambda is yielding the same object over and over.";
  ASSERT_FALSE(tester.is_singleton<SingletonTester>([]() { return new SingletonTester{}; }));
}

}  // namespace
