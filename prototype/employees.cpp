#include <iostream>
#include <memory>

using namespace std;

class Address
{
  string street, city;
  int suite;
  public:
    Address(const string& street, const string& city, const int& suite):
    street(street), city(city), suite(suite)
    {
  
    }

    Address(const Address& other)
    {
      street = other.street;
      city = other.city;
      suite = other.suite;
    }

    friend ostream& operator<<(ostream& os, const Address& address)
    {
      os << "Street: " << address.street << " City: " << address.city << " Suite: " << address.suite << endl;
      return os;
    }

    // Getters and Setters
    string get_street()
    {
      return street;
    }

    string get_city()
    {
      return city;
    }

    int get_suite()
    {
      return suite;
    }

    void set_street(const string& street)
    {
      this->street = street;
    }

    void set_city(const string& city)
    {
      this->city = city;
    }

    void set_suite(const int& suite)
    {
      this->suite = suite;
    }
};

class Contact
{
  string name;
  public:

    Address* address;
    Contact(string name, Address* p_address):
    name(name), address(p_address)
    {

    }

    Contact(const Contact& contact)
    {
      this->name = contact.name;
      this->address = new Address(*contact.address);
    }
    ~Contact()
    {
      delete address;
    }
  
    friend ostream& operator<<(ostream& os, const Contact& contact)
    {
      os << "Name: " << contact.name << " Address: " << *contact.address;
      return os;
    }

    void set_name(string name)
    {
      this->name = name;
    }
  
};

class EmployeeFactory
{
  public:
    static unique_ptr<Contact> new_main_office_employee(const string& name, const int suite)
    {
      Contact employee{"", new Address{"123 East Dr", "London", 0}};
      return new_employee(name, suite, employee);
    }

  private:
    static unique_ptr<Contact> new_employee(const string& name, int suite, const Contact& prototype)
    {
      Contact result{prototype};
      result.set_name(name);
      result.address->set_suite(suite);
      return make_unique<Contact>(result);
    }

};

int main()
{

  EmployeeFactory emp_factory;
  
  auto john = emp_factory.new_main_office_employee("John Doe", 123);
  auto jane = emp_factory.new_main_office_employee("Jane Smith", 103);

  cout << *john << endl;

  cout << *jane << endl;

  return 0;
}