#define CATCH_CONFIG_MAIN
#include "../src/main.cc"
#include <Catch2/catch_test_macros.hpp>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <vector>

template<typename T>
struct SumFunctor {
  T operator()(T a, T b) {
    return a + b;
  }
};

bool sum_test_case(std::vector<int64_t> &a, int64_t k) {
  using func = SumFunctor<int64_t>;

  int64_t n = a.size();
  std::vector<int64_t> res = solve<int64_t, func>(a, k);
  std::vector<int64_t> expected(n - k + 1);
  int64_t aux = 0;

  for (size_t i = 0; i < k; ++i) {
    aux += a[i];
  }

  for (size_t i = k; i <= n; ++i) {
    expected[i - k] = aux;
    aux -= a[i - k];
    aux += a[i];
  }

  return res == expected;
}

TEST_CASE("Sum functor test", "[sum]") {
  std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());// random_device is low-quality random
  for (int64_t t = 0; t < 10; ++t) {
    int64_t n = gen() % 100 + 5;
    int64_t k = std::min(gen() % 100ll + 1, n);

    std::uniform_int_distribution<int64_t> dis(1, n);
    std::vector<int64_t> a(n);
    std::generate(a.begin(), a.end(), [&]() { return dis(gen); });

    REQUIRE(sum_test_case(a, k));
  }
}
