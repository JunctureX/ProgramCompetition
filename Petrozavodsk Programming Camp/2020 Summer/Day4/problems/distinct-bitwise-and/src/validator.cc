#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 5000, "T");
  inf.readEoln();
  int sn = 0;
  for (int cas = 1; cas <= T; ++cas) {
    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    auto x = inf.readLong(0ll, 1000000000000000000ll, "x");
    inf.readEoln();
    sn += n;
    for (int i = 0; i < n; ++i) {
      auto l = inf.readLong(0ll, 1000000000000000000ll, "l");
      inf.readSpace();
      auto r = inf.readLong(0ll, 1000000000000000000ll, "r");
      inf.readEoln();
      ensuref(l <= r, "l <= r");
    }
    ensuref(sn <= 5000, "sum of n <= 5000");
  }
  inf.readEof();
  return 0;
}
