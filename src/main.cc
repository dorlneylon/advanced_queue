#include <bits/stdc++.h>
#ifdef ONPC
#include "../algo/debug.h"
#else
#define debug(...) 42
#endif
#define fr first
#define sc second
#define pb push_back
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

template<typename T, typename Functor>
struct MinimaQueue {
private:
  T default_value;// F(a, default_value) = a
public:
  vector<pair<T, T>> s1, s2;
  Functor func;
  void insert(T el);
  void pop();
  T get();

  MinimaQueue(Functor func, T default_value = numeric_limits<T>::max())
      : func(func), default_value(default_value) {}
};

template<typename T, typename Functor>
void MinimaQueue<T, Functor>::insert(T el) {
  s1.push_back({el, func(s1.size() ? s1.back().sc : default_value, el)});
}

template<typename T, typename Functor>
void MinimaQueue<T, Functor>::pop() {
  do {
    if (s2.size()) {
      s2.pop_back();
      return;
    }

    while (s1.size()) {
      ll el = s1.back().fr;
      s1.pop_back();
      s2.pb({el, func(s2.size() ? s2.back().sc : default_value, el)});
    }
  } while (s2.size());
}

template<typename T, typename Functor>
T MinimaQueue<T, Functor>::get() {
  return func(s1.size() ? s1.back().sc : default_value,
              s2.size() ? s2.back().sc : default_value);
}

template<typename T, typename Functor, const T default_value = T()>
vector<T> solve(vector<T> &a, ll k) {
  ll n = a.size();
  MinimaQueue mq(Functor{}, default_value);

  vector<T> ans;

  for (ll i = 0; i < k; ++i) {
    mq.insert(a[i]);
  }

  ans.pb(mq.get());

  for (ll l = 1, r = k; r < n; ++r, ++l) {
    debug(l, r, mq.s1, mq.s2);
    mq.pop();
    mq.insert(a[r]);
    ans.pb(mq.get());
  }

  return ans;
}