// https://docs.google.com/document/d/1dvJCzsaMlZbB8XyG789f1NQVv3-q52kiUNkCUGTANis/edit
// my submission of https://oj.vnoi.info/problem/paliny
#include<bits/stdc++.h>
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
  for (char ch: s) {
    t += '.';
    t += ch;
  }
  t += '.';
  odd_manacher(t, d);
  for (int i = 1; i <= n; i++) {
    p[i] = d[2 * i - 1] / 2;
  }
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n; string s;
  cin >> n >> s;

  odd_manacher(s, odd_center);
  even_manacher(s, even_center);

  int best = 0;

  for (int i = 1; i <= n; i++) {
    int l = i - odd_center[i], r = i + odd_center[i];
    best = max(best, r - l + 1);
    l = i - even_center[i] + 1, r = i + even_center[i];
    best = max(best, r - l + 1);
  }

  cout << best;
  return 0;
}
