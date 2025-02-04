#define all(x) (x).begin(), (x).end()

// large coordinates, 1-indexed, offline solving
// call fake_update + fake_get -> init -> update + get
struct FT {
  typedef int T;
  T func(const T& a, const T& b) { return max(a, b); }
  vector<T> fen;
  int n = 0;
  T unit;

  FT(int _n = 0, T _unit = 0) {
    n = _n;
    unit = _unit;
    fen.assign(n + 5, unit);
  }

  void update(int idx, T val) {
    assert(idx >= 1 && idx <= n);
    for (; idx <= n; idx += idx & -idx) fen[idx] = func(fen[idx], val);
  }

  T get(int idx) {
    assert(idx >= 1 && idx <= n);
    T ans = unit;
    for (; idx > 0; idx -= idx & -idx) ans = func(ans, fen[idx]);
    return ans;
  }
};

struct FT2D {
  typedef int T;
  T comb(const T& a, const T& b) { return max(a, b); }

  vector<vector<int>> nodes;
  int m, n;
  vector<FT> ft;

  FT2D(int _m = 0, int _n = 0) {
    m = _m;
    n = _n;
    ft.resize(m + 5);
    nodes.resize(m + 5);
  }

  void fake_update(int x, int y) {
    for (; x <= m; x += x & -x) nodes[x].push_back(y);
  }

  void fake_get(int x, int y) {
    for (; x > 0; x -= x & -x) nodes[x].push_back(y);
  }

  void init() {
    for (int i = 1; i <= m; i++) {
      if (nodes[i].empty())
        continue;
      sort(all(nodes[i]));
      nodes[i].resize(unique(all(nodes[i])) - nodes[i].begin());
      ft[i] = FT((int)nodes[i].size() + 5);
    }
  }

  void update(int u, int v, T val) {
    for (int x = u; x <= m; x += x & -x) {
      ft[x].update(lower_bound(all(nodes[x]), v) - nodes[x].begin() + 1, val);
    }
  }

  T get(int u, int v) {
    T ans = 0;
    for (int x = u; x > 0; x -= x & -x)
      ans = comb(ans, ft[x].get(lower_bound(all(nodes[x]), v) - nodes[x].begin() + 1));
    return ans;
  }
};
