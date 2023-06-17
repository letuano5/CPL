const int BASE = 37;
const long long MOD = 1e9 + 2277;
const char BASE_CHAR = 'a';

long long power[N];

void build_pow() {
  power[0] = 1;
  for (int i = 1; i < N; i++)
    power[i] = power[i - 1] * BASE % MOD;
}

void build_hash(long long *h, const string &s) {
  for (int i = 1; i <= s.size(); i++) {
    h[i] = (h[i - 1] * BASE + s[i - 1] - BASE_CHAR + 1) % MOD;
  }
}

long long get_hash(long long *h, int low, int high) {
  assert(low <= high && high < N);
  return (h[high] - h[low - 1] * power[high - low + 1] + MOD * MOD) % MOD;
}
