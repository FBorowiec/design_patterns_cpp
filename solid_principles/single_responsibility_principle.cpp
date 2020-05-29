/**
 * A given class should be responsible only for doing one thing and one thing only.
 * Or in other words a class should only have one reason to change.
 * Separation of concerns - diffrerent classes handling different, independent tasks/problems.
 */
#include <unistd.h>
#include <experimental/filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace solid_principles {
namespace single_responsibility_principle {

// BAD EXAMPLE
namespace bad {
struct Journal {
  Journal(const std::string& title) : title_(title) {}
  void AddEntry(const std::string& entry) {
    static int count{0};
    entries_.push_back(std::to_string(++count) + ": " + entry);
  }

  /**
   * BAD! The Journal now also needs to take care of its persistence
   * There is no more separation of concerns
   */
  void Save(const std::string& filename) {
    std::ofstream ofs(filename);
    for (auto& e : entries_) ofs << e << std::endl;
  }

 private:
  std::string title_{};
  std::vector<std::string> entries_{};
};
}  // namespace bad

// GOOD EXAMPLE
namespace good {
/**
 * GOOD! The Journal is taking care only of the title and its entries
 */
struct Journal {
  Journal(const std::string& title) : title_(title) {}

  void AddEntry(const std::string& entry) {
    static int count{0};
    entries_.push_back(std::to_string(++count) + ": " + entry);
  }

  std::vector<std::string> GetEntries() { return entries_; }

 private:
  std::string title_{};
  std::vector<std::string> entries_{};
};

/**
 * GOOD! The persistance job is done by another object
 */
struct PersistenceManager {
  static void Save(Journal& journal, const std::string& filename) {
    std::ofstream ofs(filename);
    auto entries = journal.GetEntries();
    for (auto& e : entries) ofs << e << std::endl;
  }
};
}  // namespace good

}  // namespace single_responsibility_principle
}  // namespace solid_principles

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace solid_principles::single_responsibility_principle;

TEST(SingleResponsiblityPrincipleTest, ExampleOfUsingAJournalViolatingTheSRP) {
  bad::Journal journal("My journal");
  journal.AddEntry("I went dancing the other night!");
  journal.AddEntry("My parents loved the paella I cooked!");

  journal.Save("BadlyCreatedDiary.txt");
}

TEST(SingleResponsiblityPrincipleTest, ExampleOfUsingAJournalRespectingTheSRP) {
  good::Journal journal("My journal");
  journal.AddEntry("I went dancing the other night!");
  journal.AddEntry("My parents loved the paella I cooked!");

  good::PersistenceManager pm{};
  pm.Save(journal, "WellCreatedDiary.txt");
}

}  // namespace
