long long bin_pow (long long a, long long b, long long mod = MOD) {
  long long ans = 1;
  while (b > 0) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}
