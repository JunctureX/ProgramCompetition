#include "testlib.h"
#include <functional>
#include <vector>

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 200000, "T");
  inf.readEoln();
  int sn = 0;
  for (int cas = 0; cas < T; ++cas) {
    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();
    sn += n;
    for (int i = 1; i < n; ++i) {
      inf.readInt(1, i, format("p[%d]", i + 1));
      if (i == n - 1) inf.readEoln();
      else inf.readSpace();
    }
    ensuref(sn <= 200000, "sum n <= 200000");
  }
  inf.readEof();
  return 0;
}
