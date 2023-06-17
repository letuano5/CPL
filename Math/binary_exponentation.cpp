int64_t bin_pow(int64_t a, int64_t b, int64_t mod = 1e9 + 7) {
  int64_t ans = 1;
  while (b > 0) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}
