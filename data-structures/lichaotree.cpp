struct Line {
  int64_t a = 0, b = 0;
  Line(int64_t x = 0, int64_t y = -9e18) {
    a = x;
    b = y;
  }
  int64_t eval(int64_t x) { return a * x + b; }
};

struct LCT {
  LCT *left, *right;
  int l = 0, r = 0;
  Line line;

  LCT(int low = 0, int high = 0) {
    left = right = NULL;
    l = low, r = high;
    if (low == high) {
      return;
    }
    int mid = (low + high) / 2;
    left = new LCT(low, mid);
    right = new LCT(mid + 1, high);
  }

  void add_line(Line new_line) {
    bool better_l = new_line.eval(l) >= line.eval(l);
    bool better_r = new_line.eval(r) >= line.eval(r);

    if (better_l && better_r) {
      line = new_line;
      return;
    }

    if (better_l || better_r) {
      left->add_line(new_line);
      right->add_line(new_line);
    }
  }

  int64_t get(int64_t x) {
    if (x < l || x > r) {
      return -9e18;
    }
    if (l == r) {
      return line.eval(x);
    }
    return max({line.eval(x), left->get(x), right->get(x)});
  }
};
