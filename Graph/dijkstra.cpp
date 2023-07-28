void dijkstra(int sta, vector<pair<int, int>> g[N], int64_t *d) {
  priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;
  for (int u = 0; u <= n; u++) {
    d[u] = 9e18;
  }
  d[sta] = 0;
  pq.emplace(d[sta], sta);
  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (d[u] != du)
      continue;
    for (auto [v, w] : g[u]) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pq.emplace(d[v], v);
      }
    }
  }
}
