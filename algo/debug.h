#include <bits/stdc++.h>
using namespace std;

template <typename T> void __print(T x) { cerr << x; }
template <typename T, typename V> void __print(pair<T, V> x) {
  cerr << "{";
  __print(x.first);
  cerr << ", ";
  __print(x.second);
  cerr << "}";
}
template <typename T> void __print(pair<T, T> p) {
  cerr << "{";
  __print(p.first);
  cerr << ", ";
  __print(p.second);
  cerr << "}";
}
template <typename T> void __print(vector<T> x) {
  cerr << "[ ";
  for (auto it = x.begin(); it != x.end(); ++it) {
    if (it != x.begin())
      cerr << ", ";
    __print(*it);
  }
  cerr << " ]";
}
template <typename K, typename V> void __print(unordered_map<K, V> &m) {
  cerr << "[ ";
  for (auto [k, v] : m) {
    if (k != m.begin()->first)
      cerr << ", ";
    cerr << "{ ";
    __print(k);
    cerr << ": ";
    __print(v);
    cerr << " }";
  }
  cerr << " ]";
}

template <typename K, typename V> void __print(map<K, V> &m) {
  cerr << "[ ";
  for (auto [k, v] : m) {
    if (k != m.begin()->first)
      cerr << ", ";
    cerr << "{ ";
    __print(k);
    cerr << ": ";
    __print(v);
    cerr << " }";
  }
  cerr << " ]";
}

template <typename K> void __print(set<K> &m) {
  cerr << "[ ";
  for (auto k : m) {
    if (k != *m.begin())
      cerr << ", ";
    __print(k);
  }
  cerr << " ]";
}

template <typename K> void __print(multiset<K> &m) {
  cerr << "[ ";
  for (auto k : m) {
    if (k != *m.begin())
      cerr << ", ";
    __print(k);
  }
  cerr << " ]";
}

template <typename K> void __print(unordered_set<K> &m) {
  cerr << "[ ";
  for (auto k : m) {
    if (k != *m.begin())
      cerr << ", ";
    __print(k);
  }
  cerr << " ]";
}

template <typename K> void __print(unordered_multiset<K> &m) {
  cerr << "[ ";
  for (auto k : m) {
    if (k != *m.begin())
      cerr << ", ";
    __print(k);
  }
  cerr << " ]";
}

void debug_out() { cerr << endl; }

template <typename H, typename... T> void debug_out(H h, T... t) {
  cerr << " ";
  __print(h);
  debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
