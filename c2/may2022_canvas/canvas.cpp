#include "canvas.h"

point draw(std::string x, std::string y) {
  circle c1 = compass(p0, p1);
  line l0 = straightedge(p0, p1);
  point p2 = intersection(l0, c1, 0);
  circle c2 = compass(p1, p2);
  circle c3 = compass(p2, p1);
  point p3 = intersection(c2, c3, 0);
  point p4 = intersection(c2, c3, 1);
  line l1 = straightedge(p3, p4);
  point p5 = intersection(l1, c1, 1);
  // line l2 = straightedge(p2, p5);
  // circle c4 = compass(p1, p0);
  // point p6 = intersection(l0, c4, 1);
  // circle c5 = compass(p6, p2);
  // point p7 = intersection(l2, c5, 0);
  // circle c6 = compass(p2, p7);
  // point p8 = intersection(l0, c6, 1);
  return p5;
}