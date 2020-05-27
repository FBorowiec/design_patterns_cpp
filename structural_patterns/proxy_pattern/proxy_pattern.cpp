/**
 * An interface for accessing a particular resource.
 * MOTIVATION:
 * Example:
 *  1. You are calling foo.Bar();
 *  2. This assumes that foo is in the same process as Bar();
 *  3. What if later on, you want to put all Foo-related operations into a separate process?
 *   & Can you avoid changing your code?
 *  4. Proxy helps - same interface, entirely different behavior
 *  5. This is called a Communication Proxy
 *  & Other types: logging, vritual, guarding ...
 *
 * A proxy is a class that functions as an interface to a particular resource.
 * That resource may be remote, expensive to construct,
 * or may require logging or some other added functionality.
 */
#include <memory>
#include <ostream>

namespace structural
{
namespace proxy_pattern
{

/**
 * Smart pointers are actually proxies!
 */

struct BankAccount
{
  virtual ~BankAccount() = default;
  virtual void Deposit(int amount) = 0;
  virtual void Withdraw(int amount) = 0;
};

struct CurrentAccount : public BankAccount
{
 public:
  explicit CurrentAccount(const int balance) : balance_(balance) {}

  void Deposit(int amount) override { balance_ += amount; }
  void Withdraw(int amount) override { if(amount <= balance_) balance_ -= amount; }

  friend std::ostream& operator<<(std::ostream& os, const CurrentAccount& obj)
  {
    return os << "balance: " << obj.balance_;
  }

 private:
  int balance_;
};


}  // namespace proxy_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace
{

using namespace structural::proxy_pattern;

TEST(ProxyPatternTest, UsageOfTheProxyPattern)
{
  BankAccount* a = new CurrentAccount(123);
  a->Deposit(321);
  delete a;

  auto b = std::make_shared<CurrentAccount>(123);  // Smart pointer that offers enhanced functionalities
  BankAccount* actual = b.get();  // Enhancement
  actual->Deposit(123);
}

}  // namespace
