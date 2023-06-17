// ax + by = gcd(a, b)
int extended_euclid(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  int x1, y1;
  int d = extended_euclid(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

// ax + by = c
bool find_solution(int a, int b, int c, int &x0, int &y0) {
  if (a == 0) {
    if (b == 0) {
      if (c != 0) return false;
      x0 = 0, y0 = 0;
      return true;
    }
    if (c % b) {
      return false;
    }
    x0 = 0;
    y0 = -c / b;
    return true;
  }
  if (b == 0) {
    if (c % a)
      return false;
    x0 = -c / a;
    y0 = 0;
    return true;
  }
  int g = extended_euclid(abs(a), abs(b), x0, y0);
  if (c % g)
    return false;
  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}
