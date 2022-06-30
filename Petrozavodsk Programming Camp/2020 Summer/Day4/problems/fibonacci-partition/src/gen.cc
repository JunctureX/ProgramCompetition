#include "testlib.h"
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>

using int64 = long long;

// Random sample $k$ elements from $n$ elements with equal probability.
// Time Complexity: $O(k \log k)$
template<typename Int>
std::vector<Int> random_subset(Int n, int k) {
  ensuref(n >= k, "random_subset failed: n >= k");
  std::set<Int> set;
  for (Int i = n - k; i < n; ++ i) {
    Int p = rnd.next(static_cast<Int>(0), i);
    if (set.count(p)) {
      set.insert(i);
    } else {
      set.insert(p);
    }
  }
  std::vector<Int> result;
  for (auto elem: set) {
    result.push_back(elem);
  }
  return result;
}

struct Node {
  Node *l, *r;
  int size;
  int low, high;
  int dp, mi, mx;
  void init(int _low, int _high) {
    l = r = NULL; size = 1;
    low = _low; high = _high;
    dp = high - low;
    mi = low; mx = high;
  }
  Node* update() {
    dp = high - low;
    size = 1; mi = low; mx = high;
    if (l) {
      mi = l->mi;
      size += l->size;
      dp += l->dp + (low - l->mx + 2) / 2;
    }
    if (r) {
      size += r->size;
      dp += r->dp + (r->mi - high + 2) / 2;
      mx = r->mx;
    }
    return this;
  }
};

std::vector<Node*> pool;

Node* new_node(int low, int high) {
  Node *p;
  if (pool.empty()) p = new Node();
  else {
    p = pool.back();
    pool.pop_back();
  }
  p->init(low, high);
  return p;
}

Node* del_node(Node *o) {
  if (!o) return NULL;
  pool.push_back(o);
  del_node(o->l);
  del_node(o->r);
  return NULL;
}

void print(Node *o) {
  if (!o) return;
  print(o->l);
  for (int i = o->low; i <= o->high; i += 2) printf("%d ", i);
  print(o->r);
}

int get_size(Node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rnd.next(a + b) < a;
}

// split to two parts such that: v may in the first node in the right parts
std::pair<Node*, Node*> split_by_high(Node *o, int v) {//[-inf, v), [v, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  if (o->high + 1 < v) {
    std::tie(o->r, r) = split_by_high(o->r, v);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_high(o->l, v);
    r = o;
  }
  o->update();
  return {l, r};
}

std::pair<Node*, Node*> split_by_size(Node *o, int size) {//[0, size), [size, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  int ls = get_size(o->l);
  if (ls < size) {
    std::tie(o->r, r) = split_by_size(o->r, size - ls - 1);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_size(o->l, size);
    r = o;
  }
  o->update();
  return {l, r};
}

Node* merge(Node *l, Node *r) {
  if (!l || !r) return l ? l : r;
  if (random(l->size, r->size)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

namespace fib {
Node* add(Node* root, int x) {
  if (x == 0) return root;
  if (x == 1) x = 2;
  Node *a, *s, *t, *b;
  std::tie(a, b) = split_by_high(root, x);
  if (!a && !b) return new_node(x, x);
  if (a) std::tie(a, s) = split_by_size(a, a->size - 1);
  else s = NULL;
  std::tie(t, b) = split_by_size(b, 1);
  // x is the most significant bit
  if (!t) {
    // check if merge with bit x - 2
    if (s->high + 2 == x) s->init(s->low, x);
    else s = merge(s, new_node(x, x));
    return merge(a, s);
  }
  bool done = false;
  if (x != t->low - 1) {
    // merge with bit x + 2
    if (t->low - 2 == x) t->init(x, t->high), done = true;
    // merge with bit x - 2
    if (s && s->high + 2 == x) s->init(s->low, x), done = true;
  }
  if (done) {
    // glue two node
    if (s && t && s->high == t->low) s->init(s->low, t->high), t = del_node(t);
    return merge(merge(a, s), merge(t, b));
  }
  a = merge(a, s);
  // single node
  if (t->low - 2 > x) {
    t = merge(new_node(x, x), t);
    return merge(a, merge(t, b));
  }
  if (x == t->high + 1) {
    // remove o->high and add x + 1
    if (t->low == t->high) t = del_node(t);
    else t->init(t->low, t->high - 2);
    return add(merge(a, merge(t, b)), x + 1);
  } else if (x % 2 != t->low % 2) {
    int nx = t->high + 1;
    if (x + 1 == t->low) t = del_node(t);
    else t->init(t->low, x - 1);
    return add(merge(a, merge(t, b)), nx);
  } else {
    int nx = t->high + 1, ny = t->low - 2;
    t->init(t->low + 1, x - 1);
    if (t->low > t->high) t = del_node(t);
    root = merge(a, merge(t, b));
    root = add(root, nx);
    return add(root, ny);
  }
}

Node* sub(Node* root, int x) {
  if (x == 0) return root;
  if (x == 1) x = 2;
  Node *a, *s, *t, *b;
  std::tie(a, b) = split_by_high(root, x + 1);
  std::tie(t, b) = split_by_size(b, 1);
  ensuref(t != NULL, "X should be positive");
  if (t->low <= x && x <= t->high) {
    auto remove = [](Node *o, int x) {
      if (o->low == x) o->init(x + 2, o->high);
      else if (o->high == x) o->init(o->low, x - 2);
      else {
        Node* t = new_node(x + 2, o->high);
        o->init(o->low, x - 2);
        o = merge(o, t);
      }
      if (o->low > o->high) o = del_node(o);
      return o;
    };
    int nx = 0;
    if (x % 2 == t->low % 2) t = remove(t, x);
    else t = remove(t, x + 1), nx = x - 1;
    root = merge(a, merge(t, b));
    return add(root, nx);
  } else {
    int nx = 0, nl = 0, nr = t->low - 1;
    if (x % 2 == t->low % 2) nl = x + 1;
    else nx = x - 1, nl = x + 2;
    if (t->low + 2 > t->high) t = del_node(t);
    else t->init(t->low + 2, t->high);
    if (a) std::tie(a, s) = split_by_size(a, a->size - 1);
    else s = NULL;
    if (s && nl <= nr && s->high + 2 == nl) {
      s->init(s->low, nr);
    } else if (nl <= nr) {
      s = merge(s, new_node(nl, nr));
    }
    root = merge(merge(a, s), merge(t, b));
    return add(root, nx);
  }
}
}

int main(int argc, char **argv) {
  std::vector<int> fib = {1, 1};
  for (int i = 2; fib.back() <= 1e9; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  std::vector<int64> lucas = {2, 1};
  for (int i = 2; lucas.back() <= 1e9; ++i) {
    lucas.push_back(lucas[i - 1] + lucas[i - 2]);
  }
  auto decom = [&](int n) -> std::vector<int> {
    int i = std::upper_bound(lucas.begin(), lucas.end(), n) - lucas.begin();
    std::vector<int> ret;
    for (i -= 1; i >= 2; --i) if (n >= lucas[i]) {
      ret.push_back(i);
      n -= lucas[i];
      assert(n < lucas[i]);
    }
    if (n == 1) ret.push_back(1);
    if (n == 2) ret.push_back(0);
    return ret;
  };

  registerGen(argc, argv, 1);
  auto min_n = std::atoi(argv[1]);
  auto max_n = std::atoi(argv[2]);
  auto max_b = std::atoi(argv[3]);
  auto part = std::atoi(argv[4]);
  std::vector<int> ns;
  int N = 50000;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    ns.push_back(n);
    N -= n;
  }
  if (N) ns.push_back(N);
  printf("%d\n", (int)ns.size());
  for (auto &n: ns) {
    printf("%d\n", n);
    Node *root = NULL;
    auto iv = random_subset(max_b - 2, part * 2);
    for (auto &x: iv) x += 2;
    if (part == 1) iv = {2, max_b};

    auto can_sub = [&]() {
      if (!root) return false;
      if (root->size == 1 && root->high == 2) return false;
      return true;
    };

    auto gen_sub = [&](int &a, int &b) {
      if (root->size == 1 && root->mi == root->mx) b = rnd.next(2, root->mx - 1);
      else b = rnd.next(2, root->mx);
      int d = (root->mx - b) / 2, bound = 0;
      if (d >= 30) bound = 1e9;
      else bound = 1 << d;
      bound = std::min(bound, 1000000000);
      a = -rnd.next(1, bound);
    };

    auto gen_add = [&](int &a, int &b) {
      int x = rnd.next(part);
      b = rnd.next(iv[x * 2], iv[x * 2 + 1]);
      a = rnd.next(1, 1000000000);
    };

    for (int i = 0; i < n; ++i) {
      int a, b;
      if (can_sub() && rnd.next(3) == 0) gen_sub(a, b);
      else gen_add(a, b);
      printf("%d %d\n", a, b - 1);
      fflush(stdout);
      int sign;
      std::vector<int> ret;
      if (a < 0) ret = decom(-a), sign = -1;
      else ret = decom(a), sign = 1;
      std::vector<int> add, sub;
      for (auto k: ret) {
        int x = b + k, y = b - k, s = k & 1;
        add.push_back(x);
        if (y < 0) y = -y, s ^= (y + 1) & 1;
        if (s) sub.push_back(y);
        else add.push_back(y);
      }
      if (sign == -1) std::swap(add, sub);
      for (auto &x: add) root = fib::add(root, x);
      for (auto &x: sub) root = fib::sub(root, x);
    }
  }
  return 0;
}
