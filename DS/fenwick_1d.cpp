// Support: get max/min/gcd/sum... of prefix, update point
// 1-indexed
// Tested with: https://codeforces.com/contest/1660/problem/F2

struct BIT {
  typedef int T;
  T func (T a, T b) {
    return a + b;
  }

  vector <T> fen;
  int n = 0;
  T unit = 0;

  BIT (int _n = 0, T _unit = 0) {
    n = _n;
    unit = _unit;
    fen.assign(n + 5, unit);
  }

  void update (int idx, T val) {
    for (; idx <= n; idx += idx & -idx) {
      fen[idx] = func(fen[idx], val);
    }
  }

  T get (T idx) {
    T ans = unit;
    for (; idx > 0; idx -= idx & -idx) {
      ans = func(ans, fen[idx]);
    }
    return ans;
  }
};
