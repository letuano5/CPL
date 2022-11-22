int h[N];
int par[N];
int sz[N];

int num_chain = 1;
int head_chain[N];
int id_chain[N];

int tin[N], tout[N], time_dfs;

void dfs_sz (int u) {
  sz[u] = 1;
  for (int v : g[u]) {
    if (v == par[u])
      continue;
    par[v] = u;
    h[v] = h[u] + 1;
    dfs_sz(v);
    sz[u] += sz[v];
  }
}

void dfs_hld (int u) {
  tin[u] = ++time_dfs;
  if (!head_chain[num_chain])
    head_chain[num_chain] = u;
  id_chain[u] = num_chain;

  int max_child = -1;
  for (int v : g[u]) {
    if (v == par[u])
      continue;
    if (max_child == -1 || sz[v] > sz[max_child])
      max_child = v;
  }

  if (max_child != -1) {
    dfs_hld(max_child);
  }

  for (int v : g[u]) {
    if (v == par[u] || v == max_child)
      continue;
    ++num_chain;
    dfs_hld(v);
  }

  tout[u] = time_dfs;
}

// for query or update on path (u, v):
int64_t query (int u, int v) {
  int64_t ans = -9e18;
  while (true) {
    if (!u || !v)
      break;
    if (id_chain[u] == id_chain[v]) {
      ans = max(ans, max_range(min(tin[u], tin[v]), max(tin[u], tin[v])));
      break;
    }

    int head_u = head_chain[id_chain[u]], head_v = head_chain[id_chain[v]];
    if (h[head_u] < h[head_v]) {
      swap(head_u, head_v);
      swap(u, v);
    }

    ans = max(ans, max_range(tin[head_u], tin[u]));
    u = par[head_u];
  }
  return ans;
}
