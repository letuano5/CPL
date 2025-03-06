// <O(nlogn), O(logn)>
struct Tree {
  vector<vector<int>> f;
  vector<vector<pair<int, int>>> g;
  vector<int64_t> dep;
  vector<int> h;
  int n;
  Tree(int n = 0) {
    this->n = n;
    f.assign(n + 5, vector<int>(__lg(n + 5) + 1, 0));
    g.assign(n + 5, vector<pair<int, int>>());
    dep.assign(n + 5, 0);
    h.assign(n + 5, 0);
  }
  void add_edge(int u, int v, int w = 1) {
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  void dfs(int u) {
    for (int i = 0; f[f[u][i]][i]; i++) {
      f[u][i + 1] = f[f[u][i]][i];
    }
    for (auto [v, w] : g[u]) {
      if (v == f[u][0]) {
        continue;
      }
      f[v][0] = u;
      h[v] = h[u] + 1;
      dep[v] = dep[u] + w;
      dfs(v);
    }
  }
  void init() {
    h[1] = 1;
    dfs(1);
  }
  int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    while (h[u] > h[v]) {
      u = f[u][__lg(h[u] - h[v])];
    }
    if (u == v) {
      return u;
    }
    for (int i = __lg(h[u]); i >= 0; i--) {
      if (f[u][i] != f[v][i]) {
        u = f[u][i];
        v = f[v][i];
      }
    }
    return f[u][0];
  }
  int64_t dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
  }
};

// <O(nlogn), O(1)>
#define sz(x) (int)(x).size()
struct Tree {
  vector<vector<pair<int, int>>> g;
  vector<int64_t> dep;
  vector<int> nodes;
  vector<int> pos;
  vector<int> h;
  vector<vector<int>> minHigh;
  int n;
  Tree(int n = 0) {
    this->n = n;
    g.assign(n + 5, vector<pair<int, int>>());
    minHigh.assign(2 * n + 5, vector<int>(__lg(2 * n + 5) + 5));
    dep.assign(n + 5, 0);
    h.assign(n + 5, 0);
    nodes = {0};
    pos.assign(n + 5, 0);
  }
  void add_edge(int u, int v, int w = 1) {
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  void dfs(int u, int par = -1) {
    pos[u] = nodes.size();
    nodes.push_back(u);
    for (auto [v, w] : g[u]) {
      if (v == par) {
        continue;
      }
      h[v] = h[u] + 1;
      dep[v] = dep[u] + w;
      dfs(v, u);
      nodes.push_back(u);
    }
  }
#define MIN_HIGH(x, y) (h[x] < h[y] ? (x) : (y))
  void init() {
    h[1] = 1;
    dfs(1);
    for (int i = 1; i < sz(nodes); i++) {
      minHigh[i][0] = nodes[i];
    }
    for (int j = 1; j < sz(minHigh[0]); j++) {
      for (int i = 1; i + (1 << j) <= sz(nodes); i++) {
        minHigh[i][j] = MIN_HIGH(minHigh[i][j - 1], minHigh[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int lca(int u, int v) {
    int pu = pos[u], pv = pos[v];
    if (pu > pv) swap(pu, pv);
    int k = 31 - __builtin_clz(pv - pu + 1);
    return MIN_HIGH(minHigh[pu][k], minHigh[pv - (1 << k) + 1][k]);
  }
  int64_t dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
  }
#undef MIN_HIGH
};