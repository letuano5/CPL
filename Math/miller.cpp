namespace Miller {
const vector<int> prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

int64_t multiply(int64_t a, int64_t b, int64_t c) {
  return __int128_t(a) * b % c;
}

int64_t power(int64_t a, int64_t b, int64_t c) {
  int64_t ret = 1;
  while (b > 0) {
    if (b & 1) {
      ret = multiply(ret, a, c);
    }
    a = multiply(a, a, c);
    b >>= 1;
  }
  return ret;
}

bool composite(int64_t n, int a, int64_t d, int s) {
  int64_t x = power(a, d, n);
  if (x == 1 || x == n - 1)
    return false;
  for (int r = 1; r <= s - 1; r++) {
    x = multiply(x, x, n);
    if (x == n - 1)
      return false;
  }
  return true;
}

bool check(int64_t n) {
  if (n < 5)
    return (n == 2 || n == 3 ? 1 : 0);
  int s = 0;
  long long d = n - 1;
  while (d % 2 == 0) {
    s++;
    d /= 2;
  }
  for (int p : prime) {
    if (p == n)
      return 1;
    if (p > n - 2)
      return 1;
    if (composite(n, p, d, s))
      return 0;
  }
  return 1;
}
}  // namespace Miller
