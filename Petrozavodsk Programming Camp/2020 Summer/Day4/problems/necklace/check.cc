#include "testlib.h"
#include <vector>
#include <algorithm>

using i64 = long long;

int main(int argc, char** argv) {
  registerTestlibCmd(argc, argv);
  int T = inf.readInt();
  for (int cas = 1; cas <= T; ++cas) {
    int n = inf.readInt();
    std::vector<i64> c(n), v(n);
    for (int i = 0; i < n; ++i) c[i] = inf.readInt();
    for (int i = 0; i < n; ++i) v[i] = inf.readInt();
    int jury_m = ans.readInt();
    int user_m = ouf.readInt();
    if (user_m != -1 && (user_m < 3 || user_m > n)) {
      quitf(_wa, "case #%d: expected -1 or [%d, %d]", cas, 3, n);
    }
    if (user_m == -1 && jury_m != -1) {
      quitf(_wa, "case #%d: jury has solution while participant does not", cas);
    }
    if (user_m == -1 && jury_m == -1) {
      continue;
    }
    i64 jury_sum = 0, user_sum = 0;
    for (int i = 0; i < jury_m; ++i) {
      jury_sum += v[ans.readInt() - 1];
    }
    std::vector<int> mark(n), a(user_m);
    for (int i = 0; i < user_m; ++i) {
      a[i] = ouf.readInt(1, n) - 1;
      if (mark[a[i]]) {
        quitf(_wa, "case #%d: duplicate indices", cas);
      }
      user_sum += v[a[i]];
      mark[a[i]] = 1;
    }
    for (int i = 0; i < user_m; ++i) {
      if (c[a[i]] == c[a[(i + 1) % user_m]]) {
        quitf(_wa, "case #%d:, adjacent gems have the same color", cas);
      }
    }
    if (jury_m == -1) {
      quitf(_fail, "case #%d: participant has solution while jury does not", cas);
    }
    if (jury_sum < user_sum) {
      quitf(_fail, "case #%d: participant has better solution %lld vs %lld", cas, user_sum, jury_sum);
    }
    if (user_sum < jury_sum) {
      quitf(_wa, "case #%d: jury has better solution %lld vs %lld", cas, jury_sum, user_sum);
    }
  }
  quitf(_ok, "%d cases.", T);
  return 0;
}
