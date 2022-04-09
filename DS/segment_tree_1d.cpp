// Support: update point, get ... in range
// 1-indexed
struct SegTree {
  typedef int T;
  T func (T a, T b) {
    return max(a, b);
  }

  int n;
  T unit;
  vector <T> st;

  SegTree (int _n = 0, T _unit = 0) {
    n = _n;
    unit = _unit;
    st.assign(4 * n + 5, unit);
  }

  void update (int id, int l, int r, int pos, T val) {
    if (pos < l || pos > r)
      return;
    if (l == r) {
      st[id] = val;
      return;
    }

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, pos, val);
    update(id << 1 | 1, mid + 1, r, pos, val);

    st[id] = func(st[id << 1], st[id << 1 | 1]);
  }

  T get (int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
      return 0;
    }
    if (u <= l && r <= v) {
      return st[id];
    }
    int mid = (l + r) >> 1;
    T left = get(id << 1, l, mid, u, v);
    T right = get(id << 1 | 1, mid + 1, r, u, v);
    return func(left, right);
  }

  void update (int pos, T val) {
    assert(pos >= 1 && pos <= n);
    update(1, 1, n, pos, val);
  }

  T get (int L, int R) {
    L = max(L, 1);
    R = min(R, this->n);
    return get(1, 1, n, L, R);
  }
};
