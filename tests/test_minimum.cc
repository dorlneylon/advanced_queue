#include <vector>
#define CATCH_CONFIG_MAIN
#include "../src/main.cc"
#include <Catch2/catch_test_macros.hpp>
#include <algorithm>
#include <chrono>
#include <random>
#include <set>

template<typename T>
struct MinFunctor {
  T operator()(T a, T b) {
    return std::min(a, b);
  }
};

bool min_test_case(std::vector<int64_t> &a, int64_t k) {
  using func = MinFunctor<int64_t>;

  int64_t n = a.size();
  std::vector<int64_t> res = solve<int64_t, func>(a, k);
  std::vector<int64_t> expected(n - k + 1);
  std::multiset<int64_t> aux;

  for (size_t i = 0; i < k; ++i) {
    aux.insert(a[i]);
  }

  for (size_t i = k; i <= n; ++i) {
    expected[i - k] = *aux.begin();
    aux.erase(aux.find(a[i - k]));
    aux.insert(a[i]);
  }

  return res == expected;
}

TEST_CASE("Minimum functor test", "[minimum]") {
  for (size_t t = 0; t < 10; ++t) {
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());// random_device is low-quality random
    int64_t n = gen() % 100 + 5;
    int64_t k = std::min(gen() % 100ll + 1, n);

    std::uniform_int_distribution<int64_t> dis(1, n);
    std::vector<int64_t> a(n);
    std::generate(a.begin(), a.end(), [&]() { return dis(gen); });

    REQUIRE(min_test_case(a, k));
  }
}