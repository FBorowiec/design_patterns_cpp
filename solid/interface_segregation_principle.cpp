/**
 * Do not create interface that are too large.
 */
namespace solid
{
namespace interface_segregation_principle
{

struct Document;

namespace bad
{
struct IMachine
{
  virtual void print(Document& doc) = 0;
  virtual void scan(Document& doc) = 0;
  virtual void fax(Document& doc) = 0;
};


struct MultiFunctionPrinter : IMachine
{
  void print(Document& doc) override {}
  void scan(Document& doc) override {}
  void fax(Document& doc) override {}
};

struct Scanner : IMachine
{
  /**
   * BAD! Whatever you do you send the client a wrong message!
   * You give the API to print for a scanner that will return a dummy message at best.
   * The IMachine interface is simply too big
   */
  void print(Document& doc) override { /* BAD! What should a Scanner print? */ }
  void scan(Document& doc) override { /* Oll Korrect! */ }
  void fax(Document& doc) override { /* BAD! What should a Scanner fax? */ }
};
}  // bad

namespace good
{
/**
 * GOOD! All functionalities have their own interface now.
 * The interfaces are segregated.
 */
struct IPrinter
{
  virtual void print(Document& doc) = 0;
};

struct IScanner
{
  virtual void scan(Document& doc) = 0;
};

struct IFaxer
{
  virtual void fax(Document& doc) = 0;
};

struct Printer : IPrinter
{
  void print(Document& doc) override { /* print stuff */ }
};

// For a more complex machine you can create a new interface
struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine
{
  // Decorator pattern:
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

  void print(Document& doc) override { printer.print(doc); }
  void scan(Document& doc) override { scanner.scan(doc); }
};
}  // good

}  // interface_segregation_principle
}  // namespace solid
