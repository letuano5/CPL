// Support: update point & calc sum in range.
// 1-indexed
struct BIT{
  vector<int> fen;
  int n, unit;

  BIT(int _n = 0, int _unit = 0){
    n = _n,
    unit = _unit;
    fen.assign(_n + 5, _unit);
  }

  void reset(){
    fen.assign(n + 5, unit);
  }

  void upd(int idx, int val){
    for(; idx <= n; idx += idx & -idx)
      fen[idx] += val;
  }

  int get(int idx){
    int ans = 0;
    for(; idx > 0; idx -= idx & -idx)
      ans += fen[idx];
    return ans;
  }
};
