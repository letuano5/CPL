// O(nlog^2)
struct SA {
  int rank_[N];
  int a[N];
  int lcp[N];
  string s;
  int n;
  SA() { n = 0; }
  SA(string s) {
    this->s = s;
    s += '@';
    n = s.size();
    memset(rank_, 0, sizeof(rank_));
    memset(a, 0, sizeof(a));
    memset(lcp, 0, sizeof(lcp));
  }
  // a[i] = order of i-th suffix
  // 0-indexed
  void init() {
    vector<pair<int, int>> key(n), newkey(n);
    iota(a, a + n, 0);
    for (int i = 0; i < n; i++) {
      key[i].first = s[i];
    }
    for (int len = 1; len < n; len <<= 1) {
      for (int i = 0; i < n; i++) {
        key[i].second = key[(i + len) % n].first;
      }
      sort(a, a + n, [&](int i, int j) {
        return key[i] < key[j];
      });
      int ranking = 0;
      for (int i = 0; i < n; i++) {
        if (i > 0 && key[a[i]] != key[a[i - 1]]) {
          ranking++;
        }
        newkey[a[i]].first = ranking;
      }
      key.swap(newkey);
      if (ranking == n - 1) {
        break;
      }
    }
  }
  // lcp[i] = lcp(i-th suffix, (i+1)-th suffix)
  void kasai() {
    for (int i = 0; i < n; i++) {
      rank_[a[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
      if (rank_[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = a[rank_[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      lcp[rank_[i]] = k;
      if (k) k--;
    }
  }
  void build() {
    init();
    kasai();
  }
};

// O(nlogn)
struct SA {
  int rank_[N];
  int p[N];
  int lcp[N];
  string s;
  int n;
  SA() { n = 0; }
  SA(string s) {
    this->s = s;
    s += '@';
    n = s.size();
    memset(rank_, 0, sizeof(rank_));
    memset(p, 0, sizeof(p));
    memset(lcp, 0, sizeof(lcp));
  }
  // p[i] = order of i-th suffix
  // 0-indexed
  void init() {
    const int alphabet = 256;
    vector<int> c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
      cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
      cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
      p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
      if (s[p[i]] != s[p[i-1]])
        classes++;
      c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
      for (int i = 0; i < n; i++) {
        pn[i] = p[i] - (1 << h);
        if (pn[i] < 0)
          pn[i] += n;
      }
      fill(cnt.begin(), cnt.begin() + classes, 0);
      for (int i = 0; i < n; i++)
        cnt[c[pn[i]]]++;
      for (int i = 1; i < classes; i++)
        cnt[i] += cnt[i-1];
      for (int i = n-1; i >= 0; i--)
        p[--cnt[c[pn[i]]]] = pn[i];
      cn[p[0]] = 0;
      classes = 1;
      for (int i = 1; i < n; i++) {
        pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
        pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
        if (cur != prev)
          ++classes;
        cn[p[i]] = classes - 1;
      }
      c.swap(cn);
    }
  }
  // lcp[i] = lcp(p[i], p[i+1])
  void kasai() {
    for (int i = 0; i < n; i++) {
      rank_[p[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
      if (rank_[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = p[rank_[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      lcp[rank_[i]] = k;
      if (k) k--;
    }
  }
  void build() {
    init();
    kasai();
  }
};