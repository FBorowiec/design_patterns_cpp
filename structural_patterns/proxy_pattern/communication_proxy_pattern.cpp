/**
 * Is about relocating a certain piece of functionality someplace else.
 */
#include <iostream>
#include <string>

namespace structural {
namespace proxy_pattern {

struct Pingable {
  virtual std::wstring Ping(const std::wstring& message) = 0;
};

struct Pong : public Pingable {
  std::wstring Ping(const std::wstring& message) override { return message + L" pong"; }
};

void TryIt(Pingable& pp) { std::wcout << pp.Ping(L"ping") << "\n"; }

namespace some_web_server_away_in_space {
struct RemotePong : public Pingable {
  std::wstring result;
  std::wstring Ping(const std::wstring& message) override {
    // some complicated implementation ...
    return message + L" pong";
  }
};

}  // namespace some_web_server_away_in_space

}  // namespace proxy_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::proxy_pattern;

TEST(CommunicationProxyPatternTest, NoUsageOfTheCommunicationProxyPattern) {
  some_web_server_away_in_space::RemotePong rp;
  for (int i = 0; i < 3; i++) TryIt(rp);
}

TEST(CommunicationProxyPatternTest, ProperUsageOfTheCommunicationProxyPattern) {
  Pong pp;
  for (int i = 0; i < 3; i++) TryIt(pp);
}

}  // namespace
