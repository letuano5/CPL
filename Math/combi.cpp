// small n, k any MOD

const int MOD = 1e9 + 9;
const int N = 105;

int comb[N][N];

void prep_comb() {
  comb[0][0] = 1;
  for (int i = 1; i < N; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);
      if (comb[i][j] >= MOD)
        comb[i][j] -= MOD;
    }
  }
}

// n, k <= 10^6

const int MOD = 1e9 + 7;

int fac[N], ifac[N];

/// credit: AtCoder

int power(int x, int p) {
    int res = 1;
    while (p > 0) {
        if (p & 1) res = res * x % MOD;
        x = x * x % MOD, p >>= 1;
    }
    return res;
}

void genFac(int size) {
    fac[0] = 1;
    for (int i = 1; i <= size; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    ifac[size] = power(fac[size], MOD - 2);
    for (int i = size; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % MOD;
}

int choose(int n, int k) {
    assert(n >= k);
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}
