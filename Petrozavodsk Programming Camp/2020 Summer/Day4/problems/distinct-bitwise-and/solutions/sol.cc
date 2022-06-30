#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int M = 1e5 + 10;

struct Node {
  Node* ch[2];
  int down;
} pool[M * 60 * 2], *top;

Node* new_node() {
  top->ch[0] = top->ch[1] = NULL;
  top->down = -1;
  return top++;
}

Node* merge(Node *x, Node *y) {
  if (!x) return y;
  if (!y) return x;
  if (x->down != -1) return x;
  if (y->down != -1) return y;
  x->ch[0] = merge(x->ch[0], y->ch[0]);
  x->ch[1] = merge(x->ch[1], y->ch[1]);
  return x;
}

int64 solve(Node* o, int64 x, int d) {
  if (!o) return 0;
  if (d < 0) return 1;
  int64 ret = 0;
  if (x >> d & 1) {
    if (o->down != -1) {
      assert(o->down != 0);
      o->down -= 1;
      ret += solve(o, x, d - 1) * 2;
    } else {
      ret += solve(o->ch[0], x, d - 1);
      ret += solve(o->ch[1], x, d - 1);
    }
  } else {
    if (o->down != -1) {
      assert(o->ch[1] == NULL);
      o->down -= 1;
      ret += solve(o, x, d - 1);
    } else {
      ret += solve(merge(o->ch[0], o->ch[1]), x, d - 1);
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    int64 x;
    scanf("%d%lld", &n, &x);
    std::vector<std::pair<int64, int64>> iv(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld%lld", &iv[i].first, &iv[i].second);
    }
    std::sort(iv.begin(), iv.end());
    int m = 0;
    for (int i = 1; i < n; ++i) {
      if (iv[i].first <= iv[m].second + 1) {
        iv[m].second = std::max(iv[m].second, iv[i].second);
      } else {
        iv[++m] = iv[i];
      }
    }
    n = m + 1;
    top = pool;
    Node* root = new_node();
    for (int i = 0; i < n; ++i) {
      auto l = iv[i].first;
      auto r = iv[i].second;
      Node *p = root;
      for (int b = 59; b >= 0; --b) {
        int lb = l >> b & 1;
        int rb = r >> b & 1;
        if (lb != rb) {
          assert(p->down == -1);
          if (!p->ch[0]) p->ch[0] = new_node();
          if (!p->ch[1]) p->ch[1] = new_node();
          Node *x = p->ch[0];
          for (int j = b - 1; j >= 0; --j) {
            int o = l >> j & 1;
            if (!x->ch[1]) x->ch[1] = new_node();
            if (!o) {
              if (!x->ch[0]) x->ch[0] = new_node();
              x->ch[1]->down = j;
            }
            x = x->ch[o];
          }
          x->down = 0;
          Node *y = p->ch[1];
          for (int j = b - 1; j >= 0; --j) {
            int o = r >> j & 1;
            if (!y->ch[0]) y->ch[0] = new_node();
            if (o) {
              if (!y->ch[1]) y->ch[1] = new_node();
              y->ch[0]->down = j;
            }
            y = y->ch[o];
          }
          y->down = 0;
          break;
        } else {
          if (!p->ch[lb]) p->ch[lb] = new_node();
          p = p->ch[lb];
          if (b == 0) p->down = 0;
        }
      }
    }
    auto ret = solve(root, x, 59);
    printf("%lld\n", ret);
  }
  return 0;
}
