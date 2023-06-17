struct Dinitz {
  struct Edge {
    int u, v, cap, flow;
    Edge(int a = 0, int b = 0, int c = 0, int d = 0) {
      u = a,
      v = b;
      cap = c;
      flow = d;
    }
  };

  int n, s, t;
  vector<vector<int>> g;
  vector<Edge> edges;
  vector<int> d, ptr;

  Dinitz(int _n = 0, int _s = 0, int _t = 0) {
    n = _n;
    s = _s;
    t = _t;

    g.assign(n + 5, vector<int>());
    d.assign(n + 5, -1);
    ptr.assign(n + 5, 0);
  }

  void add_edge(int u, int v, int w) {
    g[u].emplace_back(edges.size());
    edges.emplace_back(u, v, w, 0);
    g[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0, 0);
  }

  bool bfs() {
    d.assign(n + 5, -1);
    ptr.assign(n + 5, 0);

    d[s] = 0;
    queue<int> qu;
    qu.emplace(s);

    while (!qu.empty()) {
      int u = qu.front();
      qu.pop();

      if (u == t) return true;

      for (int id : g[u]) {
        if (edges[id].flow >= edges[id].cap)
          continue;
        int v = edges[id].v;
        if (d[v] != -1)
          continue;
        d[v] = d[u] + 1;
        qu.emplace(v);
      }
    }

    return d[t] != -1;
  }

  int dfs(int u, int pushed) {
    if (u == t)
      return pushed;
    if (!pushed)
      return 0;

    for (int &id = ptr[u]; id < g[u].size(); id++) {
      int edge_id = g[u][id];
      int v = edges[edge_id].v;
      if (d[v] != d[u] + 1 || edges[edge_id].flow >= edges[edge_id].cap)
        continue;
      int x = dfs(v, min(pushed, edges[edge_id].cap - edges[edge_id].flow));
      if (x) {
        edges[edge_id].flow += x;
        edges[edge_id ^ 1].flow -= x;
        return x;
      }
    }

    return 0;
  }

  int find_flow() {
    int flow = 0;
    while (bfs()) {
      while (true) {
        int x = dfs(s, 1e9);
        if (!x) break;
        flow += x;
      }
    }
    return flow;
  }
};
