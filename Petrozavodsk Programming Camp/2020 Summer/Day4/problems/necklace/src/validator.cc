#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 200000, "T");
  inf.readEoln();
  int sn = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();
    sn += n;
    for (int i = 0; i < n; ++i) {
      inf.readInt(1, n, format("c[%d]", i + 1));
      if (i == n - 1) inf.readEoln();
      else inf.readSpace();
    }
    for (int i = 0; i < n; ++i) {
      inf.readInt(-1000000000, 1000000000, format("v[%d]", i + 1));
      if (i == n - 1) inf.readEoln();
      else inf.readSpace();
    }
    ensuref(sn <= 200000, "sum of all n <= 200000");
  }
  inf.readEof();
  return 0;
}
