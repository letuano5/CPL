/* 
 * warning: can't work with negative numbers
 * support: add/subtract/multiply two big integers, divide big integer by small integer (<= 9e18)
*/

const int BASE   = 1e9,
          DIGITS = 9;

typedef vector<int64_t> BigNum;

BigNum stringToInt(string s){
  BigNum ans;
  while(s.size() % DIGITS)
    s = '0' + s;

  for(int i = (int)s.size() - 1; i >= DIGITS - 1; i -= DIGITS){
    long long X = 0;
    for(int j = i - DIGITS + 1; j <= i; j++)
      X = X * 10 + s[j] - '0';
    ans.push_back(X);
  }

  return ans;
}

istream& operator >>(istream &stream, BigNum &X){
  string s;
  stream >> s;
  X = stringToInt(s);
  return stream;
}

ostream& operator <<(ostream &stream, const BigNum &X){
  if(X.empty()){
    stream << 0;
    return stream;
  }

  stream << X.back();
  for(int i = (int)X.size() - 2; i >= 0; i--)
    stream << setw(DIGITS) << setfill('0') << X[i];

  return stream;
}

void fix(BigNum &X){
  while(X.size() > 1 && X.back() == 0) X.pop_back();
}

bool operator < (BigNum a, BigNum b){
  if(a.size() != b.size()) return a.size() < b.size();

  for(int i = (int)a.size() - 1; i >= 0; i--)
    if(a[i] != b[i]) return a[i] < b[i];

  return 0;
}

BigNum operator +(BigNum a, BigNum b){
  int carry = 0;

  a.resize(max(a.size(), b.size()));
  b.resize(max(a.size(), b.size()));

  for(int i = 0; i < (int)a.size(); i++)
    a[i] += b[i] + carry,
    carry = a[i] >= BASE,
    a[i] %= BASE;

  if(carry) a.push_back(carry);
  fix(a);

  return a;
}


BigNum operator -(BigNum a, BigNum b){
  int carry = 0;
  a.resize(max(a.size(), b.size()));
  b.resize(max(a.size(), b.size()));

  for(int i = 0; i < (int)a.size(); i++){
    a[i] -= b[i] + carry,
    carry = a[i] < 0;
    if(a[i] < 0) a[i] += BASE;
  }

  if(carry) a.push_back(carry);
  fix(a);

  return a;
}

BigNum operator *(BigNum a, long long b){
  int carry = 0;

  for(int i = 0; i < (int)a.size(); i++){
    a[i] = a[i] * b + carry;
    carry = a[i] / BASE;
    a[i] %= BASE;
  }

  if(carry) a.push_back(carry);
  fix(a);

  return a;
}

BigNum operator *(BigNum a, BigNum b){
  BigNum res;
  int carry = 0;

  for(int i = 0; i < (int)b.size(); i++){
    BigNum tmp = a * (1LL * b[i]);
    tmp.insert(tmp.begin(), carry++, 0);
    res = res + tmp;
  }

  fix(res);
  return res;
}

long long operator % (BigNum x, long long y){
  long long ans = 0;
  for(int i = (int)x.size() - 1; i >= 0; i--)
    ans = (x[i] + 1ll * ans * BASE) % y;
  return ans;
}

BigNum operator / (BigNum x, long long y){
  int carry = 0;
  for(int i = (int)x.size() - 1; i >= 0; i--){
    long long cur = x[i] + 1ll * carry * BASE;
    x[i] = cur / y;
    carry = cur % y;
  }
  fix(x);
  return x;
}
