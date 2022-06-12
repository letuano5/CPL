// My submission of https://atcoder.jp/contests/abc255/tasks/abc255_h

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int N = 4e7 + 5; // MAX_N * LOG(VAL) * 4
const ll MOD = 998244353;
 
ll sum (ll x) {
  if (x & 1)
    return (((x + 1) / 2) % MOD * (x % MOD)) % MOD;
  return ((x / 2) % MOD * ((x + 1) % MOD)) % MOD;
}
 
ll sum (ll L, ll R) {
  ll ans = sum(R) - sum(L - 1);
  if (ans < 0) ans += MOD;
  return ans;
}
 
int cnt_nodes = 1;
struct Node {
  int left_node, right_node;
  ll val = 0, lazy = -1;
  Node (int lo = 0, int hi = 0, ll s = 0, ll lz = -1) {
    left_node = lo, right_node = hi, val = s, lz = -1;
  }
} st[N];
 
void extend(int id) {
  if (st[id].left_node == 0)
    st[id].left_node = ++cnt_nodes;
  if (st[id].right_node == 0)
    st[id].right_node = ++cnt_nodes;
}
 
void pushLazy (int id, ll l, ll r) {
  ll& lazy_val = st[id].lazy;
  extend(id);
  if (lazy_val == -1)
    return;
 
  ll mid = (l + r) >> 1ll;
  int left_node = st[id].left_node;
  int right_node = st[id].right_node;
 
  st[left_node].val = sum(l, mid) * lazy_val % MOD;
  st[right_node].val = sum(mid + 1, r) * lazy_val % MOD;
  st[left_node].lazy = st[right_node].lazy = lazy_val;
  lazy_val = -1;
}
 
void update (int id, ll l, ll r, ll u, ll v, ll val) {
  if (v < l || r < u)
    return;
  if (u <= l && r <= v) {
    st[id].val = sum(l, r) * (val % MOD) % MOD;
    st[id].lazy = val;
    return;
  }
  ll mid = (l + r) >> 1ll;
  pushLazy(id, l, r);
  update (st[id].left_node, l, mid, u, v, val);
  update (st[id].right_node, mid + 1, r, u, v, val);
  st[id].val = (st[st[id].left_node].val + st[st[id].right_node].val);
  if (st[id].val >= MOD) st[id].val -= MOD;
}
 
ll get (int id, ll l, ll r, ll u, ll v) {
  if (v < l || r < u)
    return 0;
  if (u <= l && r <= v)
    return st[id].val;
  pushLazy(id, l, r);
  ll mid = (l + r) >> 1ll;
  ll left = get(st[id].left_node, l, mid, u, v);
  ll right = get(st[id].right_node, mid + 1, r, u, v);
  left += right; if (left >= MOD) left -= MOD;
  return left;
}
 
void debug_out() { cerr << '\n'; }
template <typename Head, typename ...Tail>
void debug_out(Head H, Tail ...T){
  cerr << " " << H;
  debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
 
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
 
  ll n, q;
  cin >> n >> q;
 
  while (q--) {
    ll D, L, R;
    cin >> D >> L >> R;
    ll ans = (D % MOD) * sum(L, R) % MOD;
    ans -= get(1, 1, n, L, R);
    if (ans < 0) ans += MOD;
    cout << ans << "\n";
    assert(cnt_nodes < N);
//    debug(L, R, get(1, 1, n, L, R));
    update(1, 1, n, L, R, D % MOD);
  }
 
  return 0;
}
