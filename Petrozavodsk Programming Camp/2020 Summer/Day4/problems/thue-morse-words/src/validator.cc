#include "testlib.h"

using int64 = long long;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 1000000, "T");
  inf.readEoln();
  int su = 0;
  for (int cas = 0; cas < T; ++cas) {
    int64 n = inf.readLong(1ll, 1ll * 1000000000 * 1000000000, "n");
    inf.readEoln();
    int bound = 1000000;
    if (n <= 20) bound = std::min(bound, 1 << n);
    auto u = inf.readToken(format("[ab]{1,%d}", bound), "u");
    inf.readEoln();
    su += u.size();
    ensuref(su <= 1000000, "sum of all |u| <= 1000000");
  }
  inf.readEof();
  return 0;
}
