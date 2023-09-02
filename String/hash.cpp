mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rd(int64_t l, int64_t r) {
  return uniform_int_distribution<int64_t>(l, r)(rng);
}

struct Hash {
  /*
    static vector<int64_t> power = {1};
    vector<int64_t> Hash::power;
  */
  inline static vector<int64_t> power = {1};
  inline static int64_t BASE = -1, MOD = -1;
  vector<int64_t> h;
  bool is_prime(int64_t x) {
    for (int64_t i = 2; i * i <= x; i++) {
      if (x % i == 0) {
        return false;
      }
    }
    return x > 1;
  }
  void init() {
    if (BASE == -1) {
      do {
        BASE = rd(1e11, 1e12);
      } while (!is_prime(BASE));
    }
    if (MOD == -1) {
      do {
        MOD = rd(1e11, 1e12);
      } while (!is_prime(MOD));
    }
  }
  Hash() {
    init();
  }
  Hash(string s) {
    init();
    while ((int)power.size() <= (int)s.size() + 1) {
      power.push_back(__int128_t(power.back()) * BASE % MOD);
    }
    h.resize(s.size() + 1);
    h[0] = 0;
    for (int i = 1; i <= (int)s.size(); i++) {
      h[i] = ((__int128_t)h[i - 1] * BASE + s[i - 1]) % MOD;
    }
  }
  int64_t get(int l, int r) {
    if (l > r) {
      return 0;
    }
    __int128_t ans = h[r];
    ans -= __int128_t(h[l - 1]) * power[r - l + 1];
    ans %= MOD;
    if (ans < 0) ans += MOD;
    return ans;
  }
};
