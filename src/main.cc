#ifdef ONPC
#include "../algo/debug.h"
#else
#define debug(...) 42
#endif
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

template<typename T, typename Functor>
struct FunctorQueue {
private:
  std::vector<T> values_on, values_off;
  std::vector<T> dynamics_on, dynamics_off;

public:
  template<typename... Args>
  void emplace(Args &&...);
  void pop();
  T get();
};

template<typename T, typename Functor>
template<typename... Args>
void FunctorQueue<T, Functor>::emplace(Args &&...args) {
  values_on.emplace_back(std::forward<Args>(args)...);

  debug(values_on, values_off, dynamics_on, dynamics_off);

  if (!dynamics_on.empty()) {
    dynamics_on.push_back(Functor{}(dynamics_on.back(), values_on.back()));
  } else {
    dynamics_on.emplace_back(values_on.back());
  }

  debug(values_on, values_off, dynamics_on, dynamics_off);
}

template<typename T, typename Functor>
void FunctorQueue<T, Functor>::pop() {
  do {
    if (!values_off.empty()) {
      dynamics_off.pop_back();
      values_off.pop_back();
      return;
    }

    while (!values_on.empty()) {
      T element = values_on.back();
      values_on.pop_back();
      values_off.emplace_back(element);
      if (!values_off.empty()) {
        dynamics_off.emplace_back(Functor{}(dynamics_off.back(), element));
      } else {
        dynamics_off.emplace_back(element);
      }
    }
  } while (!values_off.empty());
}

template<typename T, typename Functor>
T FunctorQueue<T, Functor>::get() {
  assert(!values_on.empty() || !values_off.empty());
  if (values_on.empty()) {
    return dynamics_off.back();
  }
  if (values_off.empty()) {
    return dynamics_on.back();
  }
  return Functor{}(dynamics_on.back(), dynamics_off.back());
}

template<typename T, typename Functor>
std::vector<T> solve(std::vector<T> &a, int64_t k) {
  int64_t n = a.size();
  FunctorQueue<T, Functor> fq;
  std::vector<T> result;

  for (size_t i = 0; i < k; ++i) {
    fq.emplace(a[i]);
  }

  result.push_back(fq.get());

  for (size_t l = 1, r = k; r < n; ++r, ++l) {
    fq.pop();
    fq.emplace(a[r]);
    result.push_back(fq.get());
  }

  return result;
}
