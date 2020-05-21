/**
 * Connecting components together through abstractions.
 * MOTIVATION:
 * A Bridge prevents a 'Cartesian product' complexity explosion
 * Example:
 *  - Base class ThreadSchefuler
 *  - Can be preemptive or cooperative
 *  - Can run on Windows or Unix
 *  - End up with 2x2 scenario: WindowsPTS, UnitPTS, WindotwsCTS, UnixCTS
 * The Bridge pattern avoids the entity explosion.
 * It is a mechanism that decouples an interface (hierarchy) from an implementation (hierarchy).
 */
#include <iostream>
#include <string>

namespace structural
{
namespace bridge_pattern
{

}  // namespace bridge_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace
{

using namespace structural::bridge_pattern;

TEST(BridgePatternTest, UsageOfTheBridgePattern)
{

}

}  // namespace
