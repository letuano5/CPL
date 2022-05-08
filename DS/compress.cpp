// use: Compressor <type> cp;

#define all(x) (x).begin(), (x).end()
template <class T>
struct Compressor {
  vector <T> val;

  void add (int x) {
    val.push_back(x);
  }

  void init() {
    sort(all(val));
    val.resize(unique(all(val)) - val.begin());
  }

  int idx(int x) {
    return lower_bound(all(val), x) - val.begin() + 1;
  }
};
