// Interface aggregation principle: Avoid making interfaces too complex/large
// The porpuse of this principle is to provide the minimum required interface avoind exposing unnecessary functionality/features 
#include <iostream>

using namespace std;

class Document
{
  public:
    string name;
    Document(string name): name(name){};
};

class IPrinter
{
  virtual void print(Document& doc) = 0;
};

class IScanner
{
  virtual void scan(Document& doc) = 0;
};

class IFax
{
  virtual void fax(Document& doc) = 0;
};

class Printer : IPrinter
{
  public:
  void print(Document& doc) override
  {
    cout << "Printing: " << doc.name << endl;
  }
};

class Scanner : IScanner
{
  public:
  void scan(Document& doc) override
  {
    cout << "Scanning: " << doc.name << endl;
  }
};

class Fax : IFax
{
  public:
  void fax(Document& doc) override
  {
    cout << "Fax document: " << doc.name << endl;
  }
};

int main()
{
  Document doc{"No one gets out alive here"};
  Printer printer;
  Scanner scanner;
  Fax fax;

  printer.print(doc);
  scanner.scan(doc);
  fax.fax(doc);

  getchar();
  return 0;
}