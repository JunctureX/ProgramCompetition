#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 5000, "T");
  inf.readEoln();
  int sum_n = 0, sum_m = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 1000000, "m");
    inf.readEoln();
    sum_n += n;
    sum_m += m;
    ensuref(sum_n <= 5000, "sum of all n <= 5000");
    ensuref(sum_m <= 1000000, "sum of all m <= 1000000");
    for (int i = 0; i < m; ++i) {
      int l = inf.readInt(1, n, format("l[%d]", i + 1));
      inf.readSpace();
      int r = inf.readInt(1, n, format("r[%d]", i + 1));
      inf.readSpace();
      inf.readInt(1, 3, format("x[%d]", i + 1));
      inf.readEoln();
      ensuref(l <= r, "l <= r");
    }
  }
  inf.readEof();
  return 0;
}
