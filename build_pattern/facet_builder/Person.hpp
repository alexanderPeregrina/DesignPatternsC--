#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <ostream>

class PersonBuilder;

class Person
{
  std::string name;
  // Address information
  std::string street_address, post_code, city;
  
  // employment
  std::string company_name, position;
  int annual_income = 0; 

  // friend class for builders
  friend class PersonBuilder;
  friend class PersonJobBuilder;
  friend class PersonAddressBuilder;
  // friend stream operator
  friend std::ostream& operator<<(std::ostream& os, const Person& person);

  public:
    Person()
    {

    }

    Person(const std::string& name);

    static PersonBuilder create();
};
#endif //PERSON_h