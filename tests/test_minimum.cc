#include <bits/stdc++.h>
#define CATCH_CONFIG_MAIN
#include "../src/main.cc"
#include <Catch2/catch_test_macros.hpp>
using namespace std;

template<typename T>
struct MinFunctor {
  T operator()(T a, T b) {
    return min(a, b);
  }
};

bool min_test_case(vector<ll> &a, ll k) {
  using func = MinFunctor<ll>;

  ll n = a.size();
  vector<ll> res = solve<ll, func, numeric_limits<ll>::max()>(a, k);
  vector<ll> expected(n - k + 1);
  multiset<ll> aux;

  for (ll i = 0; i < k; ++i) {
    aux.insert(a[i]);
  }

  for (ll i = k; i <= n; ++i) {
    expected[i - k] = *aux.begin();
    aux.erase(aux.find(a[i - k]));
    aux.insert(a[i]);
  }

  return res == expected;
}

TEST_CASE("Minimum functor test", "[minimum]") {
  for (ll t = 0; t < 10; ++t) {
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());// random_device is low-quality random
    ll n = gen() % 100 + 5;
    ll k = min(gen() % 100ll + 1, n);

    uniform_int_distribution<ll> dis(1, n);
    vector<ll> a(n);
    generate(a.begin(), a.end(), [&]() { return dis(gen); });

    // INFO("n = " << n << ", k = " << k);
    // CHECK(min_test_case(a, k));
    REQUIRE(min_test_case(a, k));
  }
}