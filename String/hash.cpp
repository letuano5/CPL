mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rd(int64_t l, int64_t r) {
  return uniform_int_distribution<int64_t>(l, r)(rng);
}

struct Hash {
  /*
    static vector<int64_t> power = {1};
    vector<int64_t> Hash::power;
    do something with Hash::power
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
  // s is 0-indexed
  // hash is 1-indexed
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
  void push_back(char c) {
    init();
    if (power.empty()) power.emplace_back(1);
    if (h.empty()) h.emplace_back(0);
    power.emplace_back(__int128_t(power.back()) * BASE % MOD);
    h.emplace_back((__int128_t(h.back()) * BASE + c) % MOD);
  }
};

// multiple modulo
struct HashMultiMod {
  inline static const int NMOD = 2;
  inline static vector<array<int64_t, NMOD>> power = {{1, 1}};
  inline static int64_t BASE[NMOD] = {-1, -1}, MOD[NMOD] = {-1, -1};
  vector<array<int64_t, NMOD>> h;
  bool is_prime(int64_t x) {
    for (int64_t i = 2; i * i <= x; i++) {
      if (x % i == 0) {
        return false;
      }
    }
    return x > 1;
  }
  void init() {
    for (int i = 0; i < 2; i++) {
      if (BASE[i] == -1) {
        do {
          BASE[i] = rd(1e11, 1e12);
        } while (!is_prime(BASE[i]));
      }
      if (MOD[i] == -1) {
        do {
          MOD[i] = rd(1e11, 1e12);
        } while (!is_prime(MOD[i]));
      }
    }
  }
  HashMultiMod() {
    init();
  }
  HashMultiMod(string s) {
    init();
    for (const char& c : s) {
      push_back(c);
    }
  }
  array<int64_t, 2> get(int l, int r) {
    if (l > r) {
      return {0, 0};
    }
    __int128_t ans[NMOD];
    for (int i = 0; i < 2; i++) {
      ans[i] = (h[r][i] - __int128_t(h[l - 1][i]) * power[r - l + 1][i]) % MOD[i];
      if (ans[i] < 0) ans[i] += MOD[i];
    }
    return {ans[0], ans[1]};
  }
  void push_back(char c) {
    init();
    if (power.empty()) power.push_back({1, 1});
    if (h.empty()) h.push_back({0, 0});
    array<__int128_t, NMOD> bk = {h.back()[0], h.back()[1]};
    for (int i = 0; i < NMOD; i++) {
      bk[i] = bk[i] * BASE[i] + c;
      bk[i] %= MOD[i];
    }
    h.push_back(array<int64_t, NMOD>{int64_t(bk[0]), int64_t(bk[1])});
    while (power.size() < h.size()) {
      array<__int128_t, NMOD> bkk = {power.back()[0], power.back()[1]};
      for (int i = 0; i < 2; i++) {
        bkk[i] = bkk[i] * BASE[i] % MOD[i];
      }
      power.push_back(array<int64_t, 2>{int64_t(bkk[0]), int64_t(bkk[1])});
    }
  }
  void change(array<int64_t, NMOD>& cur_val, int n, int pos, char old_c, char new_c) {
    for (int i = 0; i < 2; i++) {
      cur_val[i] = (cur_val[i] - __int128_t(power[n - pos][i]) * old_c % MOD[i] + MOD[i]) % MOD[i];
      cur_val[i] = (cur_val[i] + __int128_t(power[n - pos][i]) * new_c % MOD[i] + MOD[i]) % MOD[i];
    }
  }
};
