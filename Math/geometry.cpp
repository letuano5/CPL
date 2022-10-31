typedef long double LD;
const LD eps = 1e-9;
template<typename T>
struct Point {
  T x, y;
  Point (T a = 0, T b = 0) {
    x = a;
    y = b;
  }
  friend istream& operator >> (istream &ist, Point &p) {
    ist >> p.x >> p.y;
    return ist;
  }
  Point operator + (const Point &b) const {
    return Point(x + b.x, y + b.y);
  }
  Point operator - (const Point &b) const {
    return Point(x - b.x, y - b.y);
  }
  LD dist (const Point &rhs) const {
    return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
  }
  T dot (const Point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  T cross (const Point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  bool operator < (const Point &rhs) const {
    if (fabs(x - rhs.x) <= eps)
      return y < rhs.y;
    return x < rhs.x;
  }
  bool operator == (const Point &rhs) const {
    return fabs(x - rhs.x) <= eps && fabs(y - rhs.y) <= eps;
  }
  bool operator != (const Point &rhs) const {
    return !(*this == rhs);
  }
};

template<typename T>
struct Line {
  T a, b, c;
  Line (T x = 0, T y = 0, T z = 0) {
    x = a;
    y = b;
    z = c;
  }
  Line (Point<T> A, Point<T> B) {
    a = B.y - A.y;
    b = A.x - B.x;
    c = -A.x * (B.y - A.y) + A.y * (B.x - A.x);
  }
  LD dist (const Point<T> &p) {
    return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
  }
  Point<T> intersect (const Line &other) const {
    LD D = a * other.b - other.a * b;
    LD Dx = b * other.c - other.b * c;
    LD Dy = c * other.a - other.c * a;

    if (D == 0) {
      if (Dx == 0 && Dy == 0) {
        return Point<T>(1e9, 1e9);
      }
      else {
        return Point<T>(-1e9, -1e9);
      }
    }
    else {
      return Point<T>(Dx / D, Dy / D);
    }
  }
};

struct Polygon {
  vector<Point<T>> p;
  T area = 0;

  Polygon() {}
  void add (Point<T> x) {
    p.push_back(x);
  }

  void calc_area() {
    area = 0;
    p.emplace_back(p.front());
    for (int i = 0; i + 1 < (int)p.size(); i++) {
      area += (p[i].x - p[i + 1].x) * (p[i].y + p[i + 1].y);
    }
    area = abs(area); // /2.0
    p.pop_back();
  }

  bool operator < (const Polygon &that) const {
    return area < that.area;
  }
};

