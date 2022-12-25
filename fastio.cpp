int geti(){
  int y = 0, s = 1;
  char c = getchar();
  if (c == '-')
    s = -1,
    c = getchar();

  while (isdigit(c))
    y = y * 10 + (c - '0'),
    c = getchar();

  return s*y;
}

ld getd(){
  ld y = 0, s = 1, i = 10;
  char c = getchar();
  if (c == '-')
    s = -1,
    c = getchar();

  while (isdigit(c))
    y = y * 10 + (c - '0'),
    c = getchar();

  if (c != '.')
    return s * y;
  c = getchar();
  while (isdigit(c))
    y = y + (c - '0') / i,
    i *= 10,
    c = getchar();

  return s * y;
}
