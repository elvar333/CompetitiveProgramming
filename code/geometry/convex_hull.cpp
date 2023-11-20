#include "polygon.cpp"
bool cmp(const point &a, const point &b) {
  return abs(real(a) - real(b)) > EPS ?
    real(a) < real(b) : imag(a) < imag(b); }
polygon convexHull(polygon pts) {
  sort(pts.begin(), pts.end(), cmp);
  polygon hull;
  hull.reserve(pts.size() + 1);
  for (int phase = 0; phase < 2; ++phase) {
    auto start = hull.size();
    for (auto& p : pts) {
      while (hull.size() >= start+2 &&
             ccw(p, hull.back(), hull[hull.size()-2]) <= 0)
        hull.pop_back();
      hull.push_back(p);
    }
    hull.pop_back();
    reverse(pts.begin(), pts.end());
  }
  if (hull.size() == 2 && hull[0] == hull[1]) hull.pop_back();
  return hull; }
// vim: cc=60 ts=2 sts=2 sw=2:
