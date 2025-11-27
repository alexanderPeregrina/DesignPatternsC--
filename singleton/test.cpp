#include <gtest/gtest.h>
#include "city_populations.hpp"

// To compile : g++ test.cpp city_populations.cpp -DUNIT_TESTING -lgtest -lpthread -o test.exe

// Not a good practice to depend on a actual data base information, instead 
// the singleton should be implemented using Dependency inversion
TEST(RecorFinderTest, SingletonTotalPopulationTest)
{
  SingletonRecordFinder srf;
  vector<string> cities;
  cities.push_back("Tokyo");
  cities.push_back("Buenos Aires");
  int tp = srf.total_population(cities);
  EXPECT_EQ(tp, 52500000);
}

// With dependency injection
TEST(RecorFinderTest, ConfigurableRecordFinderTotalPopulation)
{
  DummyDatabase db;
  ConfigurableRecordFinder crf{db};

  int result = crf.total_population(vector<string>{"alpha", "beta"});
  EXPECT_EQ(result, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

