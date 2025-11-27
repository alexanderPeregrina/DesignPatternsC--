#include "PersonBuilder.hpp"

// PersonBuildBase Methods
PersonBuilderBase::PersonBuilderBase(Person& person): person(person)
{

}

PersonAddressBuilder PersonBuilderBase::lives()
{
  return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works()
{
    return PersonJobBuilder(person);
}

// Person Builder methods
PersonBuilder::PersonBuilder(): PersonBuilderBase(p)
{

}

PersonBuilderBase::operator Person()
{
  return std::move(person);
}

PersonBuilder& PersonBuilder::set_name(std::string name)
{
  person.name = name;
  return *this;
}

// Person Address Builder methods
PersonAddressBuilder::PersonAddressBuilder(Person& person): PersonBuilderBase(person)
{

}

PersonAddressBuilder& PersonAddressBuilder::at(std::string street_address)
{
  person.street_address = street_address;
  return *this;
}

PersonAddressBuilder& PersonAddressBuilder::with_post_code(std::string post_code)
{
  person.post_code = post_code;
  return *this;
}

PersonAddressBuilder& PersonAddressBuilder::in(std::string city)
{
  person.city = city;
  return *this;
}

// Person Job Builder methods
PersonJobBuilder::PersonJobBuilder(Person& person): PersonBuilderBase(person)
{

}

PersonJobBuilder& PersonJobBuilder::at(std::string company_name)
{
  person.company_name = company_name;
  return *this;
}

PersonJobBuilder& PersonJobBuilder::as_a(std::string position)
{
  person.position = position;
  return *this;
}

PersonJobBuilder& PersonJobBuilder::earning(int annunal_income)
{
  person.annual_income = annunal_income;
  return *this;
}

