// small coordinate, 1 - indexed
// for large coordinate, please go to "ft_2d.cpp"
struct BIT2D {
  typedef int T;

  vector <vector <T>> ft;
  int m, n;
  T unit;

  T func (T a, T b) {
    return a + b;
  }

  BIT2D (int _m = 0, int _n = 0, T _unit = 0) {
    ft.assign(_m + 5, vector <T> (_n + 5, _unit));
    unit = _unit;
    m = _m; n = _n;
  }

  void update (int _u, int _v, T val) {
    _u++;
    _v++;
    assert (_u >= 1 && _u < ft.size() && _v >= 1 && _v < ft[0].size());
    for (int u = _u; u <= m; u += u & -u) {
      for (int v = _v; v <= n; v += v & -v) {
        ft[u][v] = func(ft[u][v], val);
      }
    }
  }

  int get (int _u, int _v) {
    int ans = unit;
    _u++;
    _v++;
    assert (_u >= 1 && _u < ft.size() && _v >= 1 && _v < ft[0].size());
    for (int u = _u; u > 0; u -= u & -u) {
      for (int v = _v; v > 0; v -= v & -v) {
        ans = func(ans, ft[u][v]);
      }
    }
    return ans;
  }

  // only for sum!
  int get (int u, int v, int x, int y) {
    return get(x, y) - get(u - 1, y) - get(x, v - 1) + get(u - 1, v - 1);
  }
};
