typedef long long LL;
struct Line {
  LL a, b;
  Line (LL x = 0, LL y = 0) {
    a = x;
    b = y;
  }
  LL eval (const LL &x) const {
    return a * x + b;
  }

  // first less
  LL intersect (const Line &other) const {
    LL x = (other.b - b) / (a - other.a);
    while (eval(x) <= other.eval(x))
      x--;
    while (eval(x) > other.eval(x))
      x++;
    return x;
  }
};

struct CHT {
  deque<Line> dq;

  LL get_min (LL x) {
    assert(dq.size() >= 1);
    if (dq.size() == 1) {
      return dq[0].eval(x);
    }
    int low = 0, high = dq.size() - 2;
    long long ans = dq[0].eval(x);
    while (low <= high) {
      int mid = (low + high) / 2;
      ans = min(ans, min(dq[mid].eval(x), dq[mid + 1].eval(x)));
      if (dq[mid].eval(x) > dq[mid + 1].eval(x)) {
        low = mid + 1;
      }
      else {
        high = mid - 1;
      }
    }
    return ans;
  }

  bool better (Line last, Line before_last, Line new_line) {
    __int128_t fi = (before_last.b - last.b);
    fi *= (new_line.a - last.a);
    __int128_t se = (last.b - new_line.b);
    se *= (last.a - before_last.a);
    return fi >= se;
  }

  void add_back (LL a, LL b) {
    Line new_line(a, b);
    // dq.back().intersect(dq[dq.size() - 2]) >= new_line.intersect(dq.back())
    while (dq.size() >= 2) {
      Line last = dq.back();
      Line before_last = dq[dq.size() - 2];

      if (better(last, before_last, new_line))
        dq.pop_back();
      else
        break;
    }
    dq.push_back(new_line);
  }

  void add_front (LL a, LL b) {
    Line new_line(a, b);
    while (dq.size() >= 2) {
      Line last = dq[0];
      Line before_last = dq[1];

      if (better(new_line, before_last, last))
        dq.pop_front();
      else
        break;
    }
    dq.push_front(new_line);
  }
};
