#ifdef ONPC
#include "../algo/debug.h"
#else
#define debug(...) 42
#endif
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#define fr first
#define sc second
#define pb push_back

template<typename T, typename Functor>
struct FunctorQueue {
private:
  std::vector<std::pair<T, T>> stack_first, stack_second;
  Functor func;

public:
  void insert(T el);
  void pop();
  T get();

  FunctorQueue(Functor func) : func(func) {}
};

template<typename T, typename Functor>
void FunctorQueue<T, Functor>::insert(T el) {
  if (stack_first.size()) {
    stack_first.pb({el, func(el, stack_first.back().sc)});
    return;
  }
  stack_first.pb({el, el});
}

template<typename T, typename Functor>
void FunctorQueue<T, Functor>::pop() {
  do {
    if (stack_second.size()) {
      stack_second.pop_back();
      return;
    }

    while (stack_first.size()) {
      T el = stack_first.back().fr;
      stack_first.pop_back();
      if (stack_second.size()) {
        stack_second.pb({el, func(stack_second.back().sc, el)});
      } else {
        stack_second.pb({el, el});
      }
    }
  } while (stack_second.size());
}

template<typename T, typename Functor>
T FunctorQueue<T, Functor>::get() {
  assert(stack_first.size() || stack_second.size());
  if (!stack_first.size()) {
    return stack_second.back().sc;
  }
  if (!stack_second.size()) {
    return stack_first.back().sc;
  }
  return func(stack_first.back().sc, stack_second.back().sc);
}

template<typename T, typename Functor>
std::vector<T> solve(std::vector<T> &a, int64_t k) {
  int64_t n = a.size();
  FunctorQueue<T, Functor> mq(Functor{});
  std::vector<T> ans;

  for (size_t i = 0; i < k; ++i) {
    mq.insert(a[i]);
  }

  ans.pb(mq.get());

  for (size_t l = 1, r = k; r < n; ++r, ++l) {
    mq.pop();
    mq.insert(a[r]);
    ans.pb(mq.get());
  }

  return ans;
}
