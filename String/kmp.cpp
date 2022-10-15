vector <int> kmp (const string &s) {
  vector <int> pi(s.size(), 0);
  pi[0] = 0;
  for (int i = 1; i < (int)s.size(); i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      pi[i] = j + 1;
  }
  return pi;
}
