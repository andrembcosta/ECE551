#include "circle.h"

#include "cmath"

#define PI 3.14159265

void getAngles(const double & d,
               const double & r1,
               const double & r2,
               double & t1,
               double & t2) {
  t1 = acos((pow(r1, 2) + pow(d, 2) - pow(r2, 2)) / (2 * r1 * d));
  t2 = acos((pow(r2, 2) + pow(d, 2) - pow(r1, 2)) / (2 * r2 * d));
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.distanceFrom(otherCircle.center);
  if (distance >= radius + otherCircle.radius) {
    return 0;
  }
  if (radius >= distance + otherCircle.radius) {
    return PI * pow(otherCircle.radius, 2);
  }
  if (otherCircle.radius >= distance + radius) {
    return PI * pow(radius, 2);
  }
  double theta1;
  double theta2;
  getAngles(distance, radius, otherCircle.radius, theta1, theta2);
  double area1 = pow(radius, 2) * (theta1 - 0.5 * sin(2 * theta1));
  double area2 = pow(otherCircle.radius, 2) * (theta2 - 0.5 * sin(2 * theta2));
  return area1 + area2;
}
