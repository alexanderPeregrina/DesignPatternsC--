#include "Person.hpp"
#include "PersonBuilder.hpp"

Person::Person(const std::string& name): name(name)
{

}

PersonBuilder Person::create()
{
    return PersonBuilder();
}

// stream insertion operator
std::ostream& operator<<(std::ostream& os, const Person& person)
{
  os << "Name: " << person.name << "\n";
  os << "Address: " << person.street_address << ", " << person.city << " " << person.post_code << "\n";
  os << "Company: " << person.company_name << ", Position: " << person.position << ", Income: " << person.annual_income;
  return os;
}