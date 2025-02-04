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
