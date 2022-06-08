struct SegTree {
  typedef int T;
  T func (const T& a, const T& b) { return a + b; }
 
  int n;
  T unit;
  T unit_lazy;
  vector <T> st, lazy;
 
  SegTree (int _n = 0, T _u = 0, T _ul = -1) {
    n = _n;
    unit = _u;
    unit_lazy = _ul;
    st.assign(4 * n + 5, unit);
    lazy.assign(4 * n + 5, unit_lazy);
  }
 
  void pushLazy (int id, int l, int r) {
    if (lazy[id] == unit_lazy)
      return;
    int& add_val = lazy[id];
    int mid = (l + r) >> 1;
    st[id << 1]       = (mid - l + 1) * add_val;
    st[id << 1 | 1]   = (r - mid) * add_val;
    lazy[id << 1]     = add_val;
    lazy[id << 1 | 1] = add_val;
    add_val = unit_lazy;
  }
 
  void update (int id, int l, int r, int u, int v, T val) {
    if (v < l || r < u)
      return;
    if (u <= l && r <= v) {
      st[id] = 1ll * (r - l + 1) * val;
      lazy[id] = val;
      return;
    }
 
    int mid = (l + r) >> 1;
    pushLazy(id, l, r);
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
 
    st[id] = func(st[id << 1], st[id << 1 | 1]);
  }
 
  T get (int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
      return unit;
    }
    if (u <= l && r <= v) {
      return st[id];
    }
    pushLazy(id, l, r);
    int mid = (l + r) >> 1;
    T left = get(id << 1, l, mid, u, v);
    T right = get(id << 1 | 1, mid + 1, r, u, v);
    return func(left, right);
  }
 
  void update (int L, int R, T val) {
    assert(L <= R && L >= 1 && R <= n);
    update(1, 1, n, L, R, val);
  }
 
  T get (int L, int R) {
    L = max(L, 1);
    R = min(R, this->n);
    return get(1, 1, n, L, R);
  }
};
