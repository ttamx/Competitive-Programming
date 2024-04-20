#include "canvas.cpp"
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

long double EPS = 1e-8L;

namespace grader {
// START PARSER
class ops_node {
public:
  std::string ops;
  int value;
  ops_node *left;
  ops_node *right;
  ops_node(std::string ops, ops_node *l, ops_node *r)
      : ops(ops), left(l), right(r), value(-999) {}
  ops_node(int val, ops_node *l, ops_node *r)
      : ops(""), left(l), right(r), value(val) {}
  int convert(std::vector<node> &nodes) {
    int lidx = -1;
    if (left)
      lidx = left->convert(nodes);
    node cur;
    cur.ops = ops;
    cur.value = value;
    int cidx = nodes.size();
    nodes.push_back(cur);
    int ridx = -1;
    if (right)
      ridx = right->convert(nodes);
    nodes[cidx].left = lidx;
    nodes[cidx].right = ridx;
    return cidx;
  }
};

std::vector<std::string> tokenize(std::string s) {
  std::vector<std::string> tokens;
  std::string cur;
  for (char c : s) {
    if (c == '(') {
      if (!cur.empty()) {
        tokens.push_back(cur);
        cur.clear();
      }
      tokens.push_back("(");
    } else if (c == ')') {
      if (!cur.empty()) {
        tokens.push_back(cur);
        cur.clear();
      }
      tokens.push_back(")");
    } else if (c == ',') {
      if (!cur.empty()) {
        tokens.push_back(cur);
        cur.clear();
      }
      tokens.push_back(",");
    } else {
      cur.push_back(c);
    }
  }
  if (!cur.empty())
    tokens.push_back(cur);
  return tokens;
}

ops_node *parse(std::string s) {
  std::vector<std::string> opstr;
  std::vector<ops_node *> nodes;
  for (std::string token : tokenize(s)) {
    if (token[0] == ')') {
      if (opstr.back() == "SQRT") {
        nodes.back() = new ops_node("SQRT", nodes.back(), nullptr);
      } else {
        ops_node *r = nodes.back();
        nodes.pop_back();
        ops_node *l = nodes.back();
        nodes.pop_back();
        nodes.push_back(new ops_node(opstr.back(), l, r));
      }
      opstr.pop_back();
    } else if (token[0] == '(') {
      ;
    } else if (token[0] == ',') {
      ;
    } else if (isdigit(token.back())) {
      nodes.push_back(new ops_node(std::stoi(token), nullptr, nullptr));
    } else {
      opstr.push_back(token);
    }
  }
  return nodes.back();
}

std::pair<std::vector<node>, int> convert_ops(ops_node *opn) {
  std::vector<node> all;
  int root = opn->convert(all);
  return make_pair(all, root);
}
// END PARSER

std::vector<point> ps;
std::vector<line> ls;
std::vector<circle> cs;

long double det(point p1, point p2) { return p1.x * p2.y - p1.y * p2.x; }

void draw(std::string x, std::string y);

// private
void failed(std::string msg) {
  std::cout << "!x " << msg << std::endl;
  exit(0);
}

int count;

void counter() {
  count++;
  if (count > 5000)
    failed("too many function calls");
}
bool check(point p) {
  return p.index < ps.size() && ps[p.index].x == p.x && ps[p.index].y == p.y;
}
bool check(line l) {
  return l.index < ls.size() && ls[l.index].p1.index == l.p1.index &&
         ls[l.index].p2.index == l.p2.index && check(l.p1) && check(l.p2);
}
bool check(circle c) {
  return c.index < cs.size() && cs[c.index].p.index == c.p.index &&
         check(c.p) && cs[c.index].r == c.r;
}
std::string to_string(point p) { return "P" + std::to_string(p.index); }
std::string to_string(line l) { return "L" + std::to_string(l.index); }
std::string to_string(circle c) { return "C" + std::to_string(c.index); }

std::string add_point(point &p) {
  p = point(ps.size(), p.x, p.y);
  ps.push_back(p);
  return "P" + std::to_string(p.index);
}

std::string add_circle(circle &c) {
  c = circle(cs.size(), c.p, c.r);
  cs.push_back(c);
  return "C" + std::to_string(c.index);
}

std::string add_line(line &l) {
  l = line(ls.size(), l.p1, l.p2);
  ls.push_back(l);
  return "L" + std::to_string(l.index);
}

long double sq(long double x) { return x * x; }

std::vector<point> intersects_v(const point &p1, const point &p2,
                                const point &cp, long double r,
                                bool segment = false) {
  // Based on https://rosettacode.org/wiki/Line_circle_intersection#C.2B.2B
  std::vector<point> res;
  auto x0 = cp.x;
  auto y0 = cp.y;
  auto x1 = p1.x;
  auto y1 = p1.y;
  auto x2 = p2.x;
  auto y2 = p2.y;
  auto A = y2 - y1;
  auto B = x1 - x2;
  auto C = x2 * y1 - x1 * y2;
  auto a = sq(A) + sq(B);
  long double b, c;
  bool bnz = true;
  if (std::abs(B) >= EPS) {
    b = 2 * (A * C + A * B * y0 - sq(B) * x0);
    c = sq(C) + 2 * B * C * y0 - sq(B) * (sq(r) - sq(x0) - sq(y0));
  } else {
    b = 2 * (B * C + A * B * x0 - sq(A) * y0);
    c = sq(C) + 2 * A * C * x0 - sq(A) * (sq(r) - sq(x0) - sq(y0));
    bnz = false;
  }
  auto d = sq(b) - 4 * a * c; // discriminant
  if (d < 0) {
    return res;
  }

  // checks whether a point is within a segment
  auto within = [x1, y1, x2, y2](long double x, long double y) {
    auto d1 = sqrt(sq(x2 - x1) + sq(y2 - y1)); // distance between end-points
    auto d2 = sqrt(sq(x - x1) + sq(y - y1));   // distance from point to one end
    auto d3 = sqrt(sq(x2 - x) + sq(y2 - y)); // distance from point to other end
    auto delta = d1 - d2 - d3;
    return abs(delta) < EPS; // true if delta is less than a small tolerance
  };

  auto fx = [A, B, C](long double x) { return -(A * x + C) / B; };

  auto fy = [A, B, C](long double y) { return -(B * y + C) / A; };

  auto rxy = [segment, &res, within](long double x, long double y) {
    if (!segment || within(x, y)) {
      res.push_back(point(-1, x, y));
    }
  };

  long double x, y;
  if (d == 0.0L) {
    // line is tangent to circle, so just one intersect at most
    if (bnz) {
      x = -b / (2 * a);
      y = fx(x);
      rxy(x, y);
    } else {
      y = -b / (2 * a);
      x = fy(y);
      rxy(x, y);
    }
  } else {
    // two intersects at most
    d = sqrt(d);
    if (bnz) {
      x = (-b + d) / (2 * a);
      y = fx(x);
      rxy(x, y);
      x = (-b - d) / (2 * a);
      y = fx(x);
      rxy(x, y);
    } else {
      y = (-b + d) / (2 * a);
      x = fy(y);
      rxy(x, y);
      y = (-b - d) / (2 * a);
      x = fy(y);
      rxy(x, y);
    }
  }

  return res;
}

std::vector<point> intersection_v(circle c1, circle c2) {
  // circle 1: (x0, y0), radius r0
  // circle 2: (x1, y1), radius r1
  long double x0 = c1.p.x;
  long double y0 = c1.p.y;
  long double r0 = c1.r;
  long double x1 = c2.p.x;
  long double y1 = c2.p.y;
  long double r1 = c2.r;

  long double d = std::sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));

  std::vector<point> v;
  // non intersecting
  if (d > r0 + r1)
    return v;

  // One circle within other
  if (d < abs(r0 - r1))
    return v;

  // coincident circles
  if (d == 0 && r0 == r1) {
    return v;
  } else {
    long double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    long double h = std::sqrt(r0 * r0 - a * a);
    long double x2 = x0 + a * (x1 - x0) / d;
    long double y2 = y0 + a * (y1 - y0) / d;
    long double x3 = x2 + h * (y1 - y0) / d;
    long double y3 = y2 - h * (x1 - x0) / d;

    long double x4 = x2 - h * (y1 - y0) / d;
    long double y4 = y2 + h * (x1 - x0) / d;

    std::vector<point> res;
    res.emplace_back(-1, x3, y3);
    res.emplace_back(-1, x4, y4);
    return res;
  }
}

point intersection_v(line l1, line l2) {
  point xdiff(-1, l1.p1.x - l1.p2.x, l2.p1.x - l2.p2.x);
  point ydiff(-1, l1.p1.y - l1.p2.y, l2.p1.y - l2.p2.y);

  long double div = det(xdiff, ydiff);
  if (std::abs(div) < EPS) {
    // raise Exception('lines do not intersect')
    failed("Either lines do not intersect or lines completely intersect");
    return point(-1, 0, 0);
  } else {
    point d(-1, det(l1.p1, l1.p2), det(l2.p1, l2.p2));
    long double x = det(d, xdiff) / div;
    long double y = det(d, ydiff) / div;
    return point(-1, x, y);
  }
}

long double dist(point p1, point p2) {
  long double dx = p1.x - p2.x;
  long double dy = p1.y - p2.y;
  return std::sqrt(dx * dx + dy * dy);
}

} // namespace grader

/* --------- public interface -------------------- */
circle compass(point p1, point p2) {
  grader::counter();
  // check if both point exists;
  if (!grader::check(p1) || !grader::check(p2))
    grader::failed("compass called with unknown args");
  if (p1.index == p2.index)
    grader::failed("compass called with duplicated points");
  long double r = grader::dist(p1, p2);
  circle c(-1, p1, r);
  std::cout << grader::add_circle(c) << " COM " << grader::to_string(p1) << " "
            << grader::to_string(p2) << "\n";
  return c;
}

line straightedge(point p1, point p2) {
  grader::counter();
  if (!grader::check(p1) || !grader::check(p2))
    grader::failed("straightedge called with unknown args");
  if (p1.index == p2.index)
    grader::failed("straightedge called with duplicated points");
  line l(-1, p1, p2);
  std::cout << grader::add_line(l) << " LIN " << grader::to_string(p1) << " "
            << grader::to_string(p2) << "\n";
  return l;
}

point intersection(line l1, line l2) {
  grader::counter();
  if (!grader::check(l1) || !grader::check(l2))
    grader::failed("line-line intersection called with unknown args");
  point p(grader::intersection_v(l1, l2));
  std::cout << grader::add_point(p) << " INT " << grader::to_string(l1) << " "
            << grader::to_string(l2) << "\n";
  return p;
}

point intersection(circle c, line l, int idx) {
  grader::counter();
  if (!grader::check(c) || !grader::check(l))
    grader::failed("circle-line intersection called with unknown args");
  std::vector<point> vp = grader::intersects_v(l.p1, l.p2, c.p, c.r);
  if (idx >= vp.size())
    grader::failed("circle-line intersection index out of bound");
  std::sort(vp.begin(), vp.end(), [](const point &p1, const point &p2) {
    return std::make_pair(p1.x, p1.y) < std::make_pair(p2.x, p2.y);
  });
  point p(vp[idx]);
  std::cout << grader::add_point(p) << " INT " << grader::to_string(c) << " "
            << grader::to_string(l) << " " << idx << "\n";
  return p;
}

point intersection(line l, circle c, int idx) {
  return intersection(c, l, idx);
}

point intersection(circle c1, circle c2, int idx) {
  grader::counter();
  if (!grader::check(c1) || !grader::check(c2))
    grader::failed("circle-circle called with unknown args");
  std::vector<point> vp = grader::intersection_v(c1, c2);
  if (idx >= vp.size())
    grader::failed("circle-circle intersection index out of bound");
  std::sort(vp.begin(), vp.end(), [](const point &p1, const point &p2) {
    return std::make_pair(p1.x, p1.y) < std::make_pair(p2.x, p2.y);
  });
  point p(vp[idx]);
  std::cout << grader::add_point(p) << " INT " << grader::to_string(c1) << " "
            << grader::to_string(c2) << " " << idx << "\n";
  return p;
}

std::pair<std::vector<node>, int> parse(std::string line) {
  return grader::convert_ops(grader::parse(line));
}

int main() {
  // freopen("output.txt","w",stdout);
  grader::ps.push_back(p0);
  grader::ps.push_back(p1);
  std::string a, b;
  std::cin >> a >> b;
  grader::count = 0;
  point ret = draw(a, b);
  if (!grader::check(ret))
    grader::failed("return value of draw is unknown");
  std::cout << "!! " << grader::to_string(ret) << "\n";
  return 0;
}