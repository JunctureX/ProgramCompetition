#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 500, "T");
  inf.readEoln();
  int sn = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(n, 300000, "m");
    inf.readEoln();
    sn += n;
    ensuref(sn <= 500, "sum of all n <= 500");
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      a[i] = inf.readInt(1, m, format("a[%d]", i + 1));
      if (i == n - 1) inf.readEoln();
      else inf.readSpace();
      for (int j = 0; j < i; ++j) {
        ensuref(a[i] != a[j], "if i != j, a[i] != a[j]");
      }
    }
  }
  inf.readEof();
  return 0;
}
