#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H
#include "Person.hpp"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
  protected:
    Person& person;
  public:
    PersonBuilderBase(Person& person);

    PersonAddressBuilder lives();

    PersonJobBuilder works();
    // Operator to tranform PersonBuilderBase into Person
    operator Person();
};

class PersonBuilder : public PersonBuilderBase
{
  Person p;
  public: 
  PersonBuilder();

  PersonBuilder& set_name(std::string name);
};

class PersonAddressBuilder : public PersonBuilderBase
{
  public:
    PersonAddressBuilder(Person& person);

    PersonAddressBuilder& at (std::string street_address);

    PersonAddressBuilder& with_post_code (std::string post_code);

    PersonAddressBuilder& in (std::string city);
    
};

class PersonJobBuilder : public PersonBuilderBase
{
  public: 
    PersonJobBuilder(Person& person);

    PersonJobBuilder& at (std::string company_name);

    PersonJobBuilder& as_a (std::string position);

    PersonJobBuilder& earning(int annual_income);
};

#endif