template<typename T>
struct Matrix {
  vector <vector <T>> a;

  Matrix (int r, int c) {
    a.assign(r, vector <T> (c, 0));
  }

  int row() const { return a.size(); }
  int col() const { return a[0].size(); }

  friend ostream& operator << (ostream& ost, const Matrix& x) {
    for (const auto& i : x.a) {
      for (const auto& j : i)
        ost << j << " ";
      ost << "\n";
    }
    return ost;
  }

  Matrix identity (int n) {
    Matrix ans(n, n);
    for (int i = 0; i < n; i++)
      ans.a[i][i] = 1;
    return ans;
  }

  Matrix operator * (const Matrix& rhs) const {
    Matrix lhs = *this;
    Matrix ans(lhs.row(), rhs.col());

    for (int i = 0; i < lhs.row(); i++)
      for (int j = 0; j < rhs.col(); j++)
        for (int k = 0; k < lhs.col(); k++) {
          (ans.a[i][j] += lhs.a[i][k] * rhs.a[k][j]);
        }
    return ans;
  }

  Matrix power (int64_t b) {
    Matrix a = *this, ans = identity(row());
    while (b > 0) {
      if (b & 1)
        ans = ans * a;
      a = a * a;
      b >>= 1;
    }
    return ans;
  }
};
