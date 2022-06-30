#include "testlib.h"

using i64 = long long;

bool is_prime(int n) {
  if (n < 2) return false;
  if (n < 4) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  i64 n = inf.readLong(1, 1000000000000000000ll, "n");
  inf.readSpace();
  i64 l = inf.readLong(0, n, "l");
  inf.readSpace();
  i64 r = inf.readLong(l, n, "r");
  inf.readSpace();
  int p = inf.readInt(2, 1000000, "p");
  inf.readEoln();
  ensuref(is_prime(p), "p is prime");
  inf.readEof();
  return 0;
}
