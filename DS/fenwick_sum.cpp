
// add + sum range, 1 - indexed
template <class T>
struct FT {
  vector<T> ft;
  FT(int _n = 0) {
    ft.assign(_n + 5, 0);
  }
  void upd(int id, T val) {
    for (; id < (int)ft.size(); id += id & -id) ft[id] += val;
  }
  T get(int id) {
    T ans = 0;
    for (; id > 0; id -= id & -id) ans += ft[id];
    return ans;
  }
  int lower_bound(T x) {
    int pos = 0;
    T sum = 0;
    for (int i = 19; i >= 0; i--) {
      if (pos + (1 << i) < ft.size() && sum + ft[pos + (1 << i)] < x) {
        sum += ft[pos + (1 << i)];
        pos += 1 << i;
      }
    }
    return pos + 1;
  }
};

template <class T>
struct FT2 {
  FT<T> ft1, ft2;
  int n;
  FT2(int _n = 0) {
    ft1 = FT<T>(_n + 5);
    ft2 = FT<T>(_n + 5);
    n = _n;
  }
  void upd(int l, int r, T val) {
    ft1.upd(l, (n - l + 1) * val);
    ft1.upd(r + 1, -(n - r) * val);
    ft2.upd(l, val);
    ft2.upd(r + 1, -val);
  }
  T pre(int id) {
    return ft1.get(id) - ft2.get(id) * (n - id);
  }
  T sum(int low, int high) {
    return pre(high) - pre(low - 1);
  }
};
