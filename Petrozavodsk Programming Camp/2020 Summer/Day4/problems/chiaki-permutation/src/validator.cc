#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 50, "T");
  inf.readEoln();
  int sum = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(1, 50, "n");
    inf.readEoln();
    sum += n;
    std::vector<int> mark(n);
    for (int i = 0; i < n; ++i) {
      int p = inf.readInt(0, n, format("p[%d]", i + 1));
      if (i == n - 1) inf.readEoln();
      else inf.readSpace();
      if (p == 0) continue;
      ensuref(!mark[p - 1], "input is a permutation");
      mark[p - 1] = 1;
    }
    ensuref(sum <= 50, "sum of all n <= 50");
  }
  inf.readEof();
  return 0;
}
