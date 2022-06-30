#include "testlib.h"
#include <cassert>
#include <algorithm>

void gen_anti(int n, int m) {
  std::vector<std::string> s(n);
  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) {
    s[i].resize(m, '0');
    for (int j = 0; j < m; ++j) {
      putchar('0' + ((__builtin_popcount(j) % 2) ^ (__builtin_popcount(i) % 2)));
    }
    puts("");
  }
}

void gen_fibo(int n, int m) {
  std::string a = "1", b = "0", c = "01";
  while (c.size() < n || c.size() < m) {
    c = b + a;
    a = b;
    b = c;
  }
  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      putchar('0' + ((c[i] - '0') ^ (c[j] - '0')));
    }
    puts("");
  }
}

std::string gen_str(int n) {
  std::string s;
  int xs = rnd.next(1, std::min(n, 3));
  for (int i = 0; i < xs; ++i) s += char('0' + rnd.next(2));
  while (s.size() < n) {
    if (s.size() * 2 <= n) {
      int m = s.size();
      for (int i = m - 1; i >= 0; --i) s += s[i];
    } else {
      bool rev = rnd.next(2);
      if (rev) std::reverse(s.begin(), s.end());
      while (s.size() < n) s += char('0' + rnd.next(2));
      if (rev) std::reverse(s.begin(), s.end());
    }
    int extra = rnd.next(0, std::min<int>(n - s.size(), 3));
    if (extra) {
      bool rev = rnd.next(2);
      if (rev) std::reverse(s.begin(), s.end());
      for (int i = 0; i < extra; ++i) {
        s += char('0' + rnd.next(2));
      }
      if (rev) std::reverse(s.begin(), s.end());
    }
  }
  return s;
}

void gen_rand(int n, int m) {
  std::string s = gen_str(n);
  std::string t = gen_str(m);
  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      putchar('0' + ((s[i] - '0') ^ (t[j] - '0')));
    }
    puts("");
  }
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int min_s = std::atoi(argv[1]);
  int max_s = std::atoi(argv[2]);
  int min_n = std::atoi(argv[3]);
  int max_n = std::atoi(argv[4]);
  int type = std::atoi(argv[5]);
  std::vector<int> ss;
  int S = 1000000;
  while (S >= min_s) {
    int s = rnd.next(min_s, std::min(S, max_s));
    S -= s;
    ss.push_back(s);
  }
  int T = ss.size();
  printf("%d\n", T);
  for (int i = 0; i < T; ++i) {
    int n = rnd.next(min_n, max_n);
    int m = ss[i] / n;
    if (type == 0) gen_anti(n, m);
    else if (type == 1) gen_fibo(n, m);
    else gen_rand(n, m);
  }
  return 0;
}
