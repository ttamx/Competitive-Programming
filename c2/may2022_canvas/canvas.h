#include <string>
#include <utility>
#include <vector>

class point {
public:
  int index;
  long double x, y;
  point() : index(-1), x(0), y(0) {}
  point(int idx, long double x, long double y) : index(idx), x(x), y(y) {}
  point(const point &other) : index(other.index), x(other.x), y(other.y) {}
};

class line {
public:
  int index;
  point p1, p2;
  line() : index(-1), p1(), p2() {}
  line(int idx, point p1, point p2) : index(idx), p1(p1), p2(p2) {}
};

class circle {
public:
  int index;
  point p;
  long double r;
  circle() : index(-1), p(), r(0) {}
  circle(int idx, point p, long double r) : index(idx), p(p), r(r) {}
};

struct node {
  std::string ops;
  int value = -999;
  int left = -1;
  int right = -1;
};

point draw(std::string x, std::string y);
circle compass(point p1, point p2);
line straightedge(point p1, point p2);
point intersection(line l1, line l2);
point intersection(circle c, line l, int idx);
point intersection(line l, circle c, int idx);
point intersection(circle c1, circle c2, int idx);
const point p0(0, 0.0L, 0.0L);
const point p1(1, 0.0L, 1.0L);
std::pair<std::vector<node>, int> parse(std::string line);