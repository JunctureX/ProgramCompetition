#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 1000000, "T");
  inf.readEoln();
  int sum = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();
    sum += std::max(n, m);
    ensuref(sum <= 1000000, "sum of all max(n, m) <= 1000000");
    for (int i = 0; i < n; ++i) {
      inf.readInt(1, 3, format("a[%d]", i + 1));
      if (i != n - 1) inf.readSpace();
      else inf.readEoln();
    }
    for (int i = 0; i < m; ++i) {
      inf.readInt(1, 3, format("b[%d]", i + 1));
      if (i != m - 1) inf.readSpace();
      else inf.readEoln();
    }
  }
  inf.readEof();
  return 0;
}
