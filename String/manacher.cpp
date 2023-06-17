// https://docs.google.com/document/d/1dvJCzsaMlZbB8XyG789f1NQVv3-q52kiUNkCUGTANis/edit
// my submission of https://cses.fi/problemset/task/1111/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const char DUMMY = '.';

// 1-indexed
int odd_center[N];
int even_center[N];
int d[N * 2];

void odd_manacher(string s, int *p) {
  int n = s.size();
  s = DUMMY + s + DUMMY;
  int l = 0, r = -1;

  int dem = 0;

  for (int i = 1; i <= n; i++) {
    if (i > r)
      p[i] = 0;
    else
      p[i] = min(r - i, p[l + (r - i)]);
    while (i - p[i] >= 1 && i + p[i] <= n && s[i - p[i]] == s[i + p[i]])
      p[i]++;
    p[i]--;

    if (i + p[i] > r)
      l = i - p[i],
      r = i + p[i];
  }
}

void even_manacher(string s, int *p) {
  int n = s.size();
  string t = "";
  for (char ch : s) {
    t += '.';
    t += ch;
  }
  t += '.';
  odd_manacher(t, d);
  for (int i = 1; i <= n; i++) {
    p[i] = d[2 * i - 1] / 2;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string s;
  cin >> s;
  int n = s.size();

  odd_manacher(s, odd_center);
  even_manacher(s, even_center);

  int best_l = -1, best_r = -1;
  s = ' ' + s;

  for (int i = 1; i <= n; i++) {
    int l = i - odd_center[i], r = i + odd_center[i];
    if (r - l + 1 > best_r - best_l + 1)
      best_l = l, best_r = r;
    l = i - even_center[i], r = i + even_center[i] - 1;
    if (l >= 1 && r <= n && l <= r && r - l + 1 > best_r - best_l + 1)
      best_l = l, best_r = r;
  }

  cout << s.substr(best_l, best_r - best_l + 1);
  return 0;
}
