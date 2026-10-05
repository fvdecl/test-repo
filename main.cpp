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

//full_size: размер зеленой свечи равен high - low (тело и обе тени)
bool test_full_size_green_candle()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return candle.full_size() == 30.0;
}

//full_size: у свечи, где все цены равны, размер нулевой
bool test_full_size_flat_candle_is_zero()
{
  Candle candle{ 100.0, 100.0, 100.0, 100.0 };

  return candle.full_size() == 0.0;
}

//full_size: у красной свечи размер положительный и не зависит от цвета
bool test_full_size_red_candle()
{
  Candle candle{ 110.0, 120.0, 90.0, 100.0 };

  return candle.full_size() == 30.0;
}

//body_size: размер тела зеленой свечи равен close - open, тени не учитываются
bool test_body_size_green_candle()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return candle.body_size() == 10.0;
}

//body_size: у доджи (open == close) тело нулевое, несмотря на тени
bool test_body_size_doji_is_zero()
{
  Candle candle{ 100.0, 110.0, 90.0, 100.0 };

  return candle.body_size() == 0.0;
}

//body_size: у красной свечи (close < open) размер тела положительный
bool test_body_size_red_candle()
{
  Candle candle{ 110.0, 120.0, 90.0, 100.0 };

  return candle.body_size() == 10.0;
}

//is_red: свеча с close < open красная
bool test_is_red_red_candle()
{
  Candle candle{ 110.0, 120.0, 90.0, 100.0 };

  return candle.is_red();
}

//is_red: зеленая свеча (close > open) не красная
bool test_is_red_green_candle()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return !candle.is_red();
}

//is_red: доджи (open == close) не красная, сравнение строгое
bool test_is_red_doji()
{
  Candle candle{ 100.0, 110.0, 90.0, 100.0 };

  return !candle.is_red();
}

//is_green: свеча с close > open зеленая
bool test_is_green_green_candle()
{
  Candle candle{ 100.0, 120.0, 90.0, 110.0 };

  return candle.is_green();
}

//is_green: красная свеча (close < open) не зеленая
bool test_is_green_red_candle()
{
  Candle candle{ 110.0, 120.0, 90.0, 100.0 };

  return !candle.is_green();
}

//is_green: доджи (open == close) не зеленая, сравнение строгое
bool test_is_green_doji()
{
  Candle candle{ 100.0, 110.0, 90.0, 100.0 };

  return !candle.is_green();
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
  tests.push_back(test_full_size_green_candle);
  tests.push_back(test_full_size_flat_candle_is_zero);
  tests.push_back(test_full_size_red_candle);
  tests.push_back(test_body_size_green_candle);
  tests.push_back(test_body_size_doji_is_zero);
  tests.push_back(test_body_size_red_candle);
  tests.push_back(test_is_red_red_candle);
  tests.push_back(test_is_red_green_candle);
  tests.push_back(test_is_red_doji);
  tests.push_back(test_is_green_green_candle);
  tests.push_back(test_is_green_red_candle);
  tests.push_back(test_is_green_doji);
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
