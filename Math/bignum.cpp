/*
 * warning: can't work with negative numbers
 * support: add/subtract/multiply two big integers, divide big integer by small integer (<= 9e18)
 */

const int BASE = 1e9,
          DIGITS = 9;

struct BigNum {
  vector<int64_t> a;
  BigNum() {
    a.clear();
  }
  auto &operator[](int i) { return a[i]; }
  const auto &operator[](int i) const { return a[i]; }
  int size() const {
    return a.size();
  }
  void pop_back() {
    a.pop_back();
  }
  void push_back(int64_t x) {
    a.push_back(x);
  }
  bool empty() const {
    return a.empty();
  }
  int64_t back() const {
    return a.back();
  }
  void resize(int x) {
    a.resize(x);
  }
  void init(string s) {
    a.clear();
    while (s.size() % DIGITS) {
      s = '0' + s;
    }
    for (int i = (int)s.size() - 1; i >= DIGITS - 1; i -= DIGITS) {
      int64_t X = 0;
      for (int j = i - DIGITS + 1; j <= i; j++) {
        X = X * 10 + s[j] - '0';
      }
      a.push_back(X);
    }
  }
  BigNum(string s) {
    init(s);
  }
  BigNum(int64_t x) {
    init(to_string(x));
  }
  friend istream &operator>>(istream &stream, BigNum &X) {
    string s;
    stream >> s;
    X = BigNum(s);
    return stream;
  }
  friend ostream &operator<<(ostream &stream, const BigNum &X) {
    if (X.empty()) {
      stream << 0;
      return stream;
    }
    stream << X.back();
    for (int i = (int)X.size() - 2; i >= 0; i--)
      stream << setw(DIGITS) << setfill('0') << X[i];
    return stream;
  }
  void fix(BigNum &X) const {
    while (X.size() > 1 && X.back() == 0) X.pop_back();
  }
  bool operator>(const BigNum &that) const {
    if (this->size() != that.size()) return this->size() > that.size();
    for (int i = (int)this->size() - 1; i >= 0; i--)
      if (a[i] != that[i]) return a[i] > that[i];
    return 0;
  }
  BigNum operator*(int64_t b) {
    BigNum a = *this;
    int carry = 0;
    for (int i = 0; i < (int)a.size(); i++) {
      a[i] = a[i] * b + carry;
      carry = a[i] / BASE;
      a[i] %= BASE;
    }
    if (carry) a.push_back(carry);
    fix(a);
    return a;
  }
  BigNum operator+(BigNum b) {
    BigNum a = *this;
    int carry = 0;
    a.resize(max(a.size(), b.size()));
    b.resize(max(a.size(), b.size()));
    for (int i = 0; i < (int)a.size(); i++) {
      a[i] += b[i] + carry;
      carry = a[i] >= BASE;
      a[i] %= BASE;
    }
    if (carry) a.push_back(carry);
    fix(a);
    return a;
  }

  BigNum operator-(BigNum b) {
    BigNum a = *this;
    int carry = 0;
    a.resize(max(a.size(), b.size()));
    b.resize(max(a.size(), b.size()));
    for (int i = 0; i < (int)a.size(); i++) {
      a[i] -= b[i] + carry;
      carry = a[i] < 0;
      if (a[i] < 0) a[i] += BASE;
    }
    if (carry) a.push_back(carry);
    fix(a);
    return a;
  }
  BigNum operator*(BigNum b) {
    BigNum a = *this;
    BigNum res = 0;
    int carry = 0;
    for (int i = 0; i < (int)b.size(); i++) {
      BigNum tmp = a * (int64_t)b[i];
      tmp.a.insert(tmp.a.begin(), carry++, 0);
      res = res + tmp;
    }
    fix(res);
    return res;
  }
  int64_t operator%(int64_t y) {
    int64_t ans = 0;
    for (int i = (int)this->size() - 1; i >= 0; i--)
      ans = (a[i] + 1ll * ans * BASE) % y;
    return ans;
  }
  BigNum operator/(int64_t y) {
    BigNum x = *this;
    int carry = 0;
    for (int i = (int)x.size() - 1; i >= 0; i--) {
      int64_t cur = x[i] + 1ll * carry * BASE;
      x[i] = cur / y;
      carry = cur % y;
    }
    fix(x);
    return x;
  }
};
