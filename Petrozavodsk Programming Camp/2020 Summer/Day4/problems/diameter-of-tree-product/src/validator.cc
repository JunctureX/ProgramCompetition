#include "testlib.h"
#include <functional>
#include <vector>

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 1000000, "T");
  inf.readEoln();
  int sm = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();
    for (int i = 1; i <= n; ++i) {
      int m = inf.readInt(1, 100000, format("m[%d]", i));
      sm += m;
      ensuref(sm <= 1000000, "sum m <= 1000000");
      std::vector<int> dsu(m);
      for (int i = 0; i < m; ++i) dsu[i] = i;
      std::function<int(int)> get = [&](int x) {
        if (x != dsu[x]) dsu[x] = get(dsu[x]);
        return dsu[x];
      };
      int root = -1;
      for (int j = 0; j < m; ++j) {
        inf.readSpace();
        int p = inf.readInt(0, m, format("p[%d][%d]", i, j + 1));
        if (p == 0) {
          ensuref(root == -1, "only one root");
          root = j;
        } else {
          int u = get(j);
          int v = get(p - 1);
          ensuref(u != v, "input is a tree");
          dsu[u] = v;
        }
      }
      ensuref(root != -1, "must have root");
      inf.readEoln();
    }
  }
  inf.readEof();
  return 0;
}
