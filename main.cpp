#include <vector>
#include <functional>
#include <iostream>

#include "candle.h"

//массив всех тестов, который мы заполняем в функции initTests
static std::vector<std::function<bool()>> tests;

//тест 1
bool test1()
{
  //пример какого-то теста
  return 42 == (41 + 1); //passed
}

//тест 2
bool test2()
{
  //пример какого-то теста
  return 42 != (41 + 1); //failed
}

//тест 3
bool test3()
{
  Candle candle{ 0.0, 3.0, 3.0, 3.0 };

  //пример какого-то теста
  return candle.high == 3.0;
}

//body_contains: цена внутри тела зеленой свечи
bool test_body_contains_price_inside_body()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return candle.body_contains(105.0);
}

//body_contains: цена в тенях свечи не входит в тело
bool test_body_contains_price_in_shadows()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return !candle.body_contains(115.0)
      && !candle.body_contains(95.0);
}

//body_contains: границы тела красной свечи (open и close) входят в тело
bool test_body_contains_red_candle_body_bounds()
{
  Candle candle{ 110.0, 120.0, 90.0, 100.0 };

  return candle.body_contains(110.0)
      && candle.body_contains(100.0);
}

//contains: цена в тени (вне тела) входит в свечу
bool test_contains_price_in_shadow()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return candle.contains(115.0);
}

//contains: цена за пределами high и low не входит в свечу
bool test_contains_price_outside_candle()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return !candle.contains(121.0)
      && !candle.contains(89.0);
}

//contains: цена ровно на high и low входит в свечу
bool test_contains_high_and_low_bounds()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return candle.contains(120.0)
      && candle.contains(90.0);
}

void initTests()
{
  tests.push_back(test1);
  tests.push_back(test2);
  tests.push_back(test3);
  tests.push_back(test_body_contains_price_inside_body);
  tests.push_back(test_body_contains_price_in_shadows);
  tests.push_back(test_body_contains_red_candle_body_bounds);
  tests.push_back(test_contains_price_in_shadow);
  tests.push_back(test_contains_price_outside_candle);
  tests.push_back(test_contains_high_and_low_bounds);
  //tests.push_back(test4);
  //tests.push_back(test5);
}

int launchTests()
{
  int total = 0;
  int passed = 0;

  for (const auto& test : tests)
  {
    std::cout << "test #" << (total + 1);
    if (test())
    {
      passed += 1;
      std::cout << " passed\n";
    }
    else
    {
      std::cout << " failed\n";
    }
    total += 1;
  }

  std::cout << "\ntests " << passed << "/" << total << " passed!" << std::endl;

  //0 = success
  return total - passed;
}

int main()
{
  initTests();
  return launchTests();
}
