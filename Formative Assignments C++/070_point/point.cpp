#include "point.h"

#include "cmath"

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double ans = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  return ans;
}
