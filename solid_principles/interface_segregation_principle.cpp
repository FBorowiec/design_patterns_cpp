/**
 * Do not create interface that are too large.
 * YAGNI - You Ain't Going to Need It!
 */
namespace solid_principles {
namespace interface_segregation_principle {

struct Document;

namespace bad {
struct IMachine {
  virtual void Print(Document& doc) = 0;
  virtual void Scan(Document& doc) = 0;
  virtual void Fax(Document& doc) = 0;
};

struct MultiFunctionPrinter : IMachine {
  void Print(Document& doc) override { (void)doc; }
  void Scan(Document& doc) override { (void)doc; }
  void Fax(Document& doc) override { (void)doc; }
};

struct Scanner : IMachine {
  /**
   * BAD! Whatever you do you send the client a wrong message!
   * You give the API to print for a scanner that will return a dummy message at best.
   * The IMachine interface is simply too big
   */
  void Print(Document& doc) override { /* BAD! What should a Scanner print? */
    (void)doc;
  }
  void Scan(Document& doc) override { /* Oll Korrect! */
    (void)doc;
  }
  void Fax(Document& doc) override { /* BAD! What should a Scanner fax? */
    (void)doc;
  }
};
}  // namespace bad

namespace good {
/**
 * GOOD! All functionalities have their own interface now.
 * The interfaces are segregated.
 */
struct IPrinter {
  virtual void Print(Document& doc) = 0;
};

struct IScanner {
  virtual void Scan(Document& doc) = 0;
};

struct IFaxer {
  virtual void Fax(Document& doc) = 0;
};

struct Printer : IPrinter {
  void Print(Document& doc) override { /* print stuff */
    (void)doc;
  }
};

// For a more complex machine you can create a new interface
struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine {
  // Decorator pattern:
  IPrinter& printer_;
  IScanner& scanner_;

  Machine(IPrinter& printer, IScanner& scanner) : printer_(printer), scanner_(scanner) {}

  void Print(Document& doc) override { printer_.Print(doc); }
  void Scan(Document& doc) override { scanner_.Scan(doc); }
};
}  // namespace good

}  // namespace interface_segregation_principle
}  // namespace solid_principles
