#ifdef ONPC
#include "../algo/debug.h"
#else
#define debug(...) 42
#endif
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

template<typename T>
using Pair = std::pair<T, T>;

template<typename T, typename Functor>
struct FunctorQueue {
private:
  std::vector<Pair<T>> stack_first, stack_second;
  Functor func;

public:
  void insert(T el);
  void pop();
  T get();

  FunctorQueue(Functor func = Functor{}) : func(func) {}
};

template<typename T, typename Functor>
void FunctorQueue<T, Functor>::insert(T el) {
  if (stack_first.size()) {
    stack_first.emplace_back(el, func(el, stack_first.back().second));
    return;
  }
  stack_first.emplace_back(el, el);
}

template<typename T, typename Functor>
void FunctorQueue<T, Functor>::pop() {
  do {
    if (!stack_second.empty()) {
      stack_second.pop_back();
      return;
    }

    while (!stack_first.empty()) {
      T el = stack_first.back().first;
      stack_first.pop_back();
      if (!stack_second.empty()) {
        stack_second.emplace_back(el, func(stack_second.back().second, el));
      } else {
        stack_second.emplace_back(el, el);
      }
    }
  } while (stack_second.size());
}

template<typename T, typename Functor>
T FunctorQueue<T, Functor>::get() {
  assert(!stack_first.empty() || !stack_second.empty());
  if (stack_first.empty()) {
    return stack_second.back().second;
  }
  if (stack_second.empty()) {
    return stack_first.back().second;
  }
  return func(stack_first.back().second, stack_second.back().second);
}

template<typename T, typename Functor>
std::vector<T> solve(std::vector<T> &a, int64_t k) {
  int64_t n = a.size();
  FunctorQueue<T, Functor> mq;
  std::vector<T> ans;

  for (size_t i = 0; i < k; ++i) {
    mq.insert(a[i]);
  }

  ans.push_back(mq.get());

  for (size_t l = 1, r = k; r < n; ++r, ++l) {
    mq.pop();
    mq.insert(a[r]);
    ans.push_back(mq.get());
  }

  return ans;
}
