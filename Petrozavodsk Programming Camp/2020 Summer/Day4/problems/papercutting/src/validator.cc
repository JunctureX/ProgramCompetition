#include "testlib.h"
#include <vector>

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
    ensuref(n <= 1000000 / m, "1 <= nm <= 1000000");
    sum += n * m;
    for (int i = 0; i < n; ++i) {
      inf.readToken(format("[0-1]{%d,%d}", m, m), format("s[%d]", i + 1));
      inf.readEoln();
    }
    ensuref(sum <= 1000000, "sum of all nm <= 1000000");
  }
  inf.readEof();
  return 0;
}
