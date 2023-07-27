/**
 * support: insert O(1) amortized, find min(ax+b) in O(log)/O(1)
 * slope must be sorted in descending order
 */

template <typename T>
struct Line {
  T a, b;
  Line(T x = 0, T y = 0) {
    a = x;
    b = y;
  }
  T eval(const T &x) const {
    return a * x + b;
  }
  T intersect(const Line &other) const {
    T x = (other.b - b) / (a - other.a);
    return x;
  }
};

template <typename T>
struct CHT {
  vector<Line<T>> dq;
  /* must use an deque here!
  T fast_get_min(const T &x) {
    // assume x > old x
    while ((d.size() > 1) && (d[1](x) <= d[0](x))) d.pop_front();
    assert(!d.empty());
    return d.front()(x);
  }
  */
  T get_min(T x) {
    if (dq.size() < 1) {
      return 9e18;
    }
    if (dq.size() == 1) {
      return dq[0].eval(x);
    }
    int low = 0, high = dq.size() - 2;
    T ans = dq[0].eval(x);
    while (low <= high) {
      int mid = (low + high) / 2;
      ans = min<T>(ans, min<T>(dq[mid].eval(x), dq[mid + 1].eval(x)));
      if (dq[mid].eval(x) > dq[mid + 1].eval(x)) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    return ans;
  }
  // or: last.intersect(before_last) >= new_line.intersect(last)
  bool better(Line<T> last, Line<T> before_last, Line<T> new_line) {
    T fi = (before_last.b - last.b);
    fi *= (new_line.a - last.a);
    T se = (last.b - new_line.b);
    se *= (last.a - before_last.a);
    return fi >= se;
  }
  void add_back(Line<T> new_line) {
    while (dq.size() && fabs(dq.back().a - new_line.a) <= 1e-9) {
      if (dq.back().b <= new_line.b) {
        return;
      }
      dq.pop_back();
    }
    while (dq.size() >= 2) {
      Line<T> last = dq.back();
      Line<T> before_last = dq[dq.size() - 2];
      if (better(last, before_last, new_line))
        dq.pop_back();
      else
        break;
    }
    dq.push_back(new_line);
  }
};
