#include <bits/stdc++.h>
using namespace std;

#define int long long

const string NAME = "a";

/*
freopen("a.inp", "r", stdin);
freopen("a.out", "w", stdout);

freopen("a.inp", "r", stdin);
freopen("a.ans", "w", stdout);
*/

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
long long get(long long l, long long h) {
  return uniform_int_distribution<long long>(l, h)(rd);
}

int32_t main() {
  for (int iTest = 1;; iTest++) {
    ofstream inp((NAME + ".inp").c_str());

    // Print test here, using inp instead of cout

    inp.close();
    system((NAME + ".exe").c_str());
    system((NAME + "_trau.exe").c_str());
    if (system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0) {
      cout << "Test " << iTest << ": WRONG!\n";
      return 0;
    }
    cout << "Test " << iTest << ": CORRECT!\n";
  }
  return 0;
}
