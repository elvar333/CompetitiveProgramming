#include "convex_hull.cpp"
double maxDist2(const polygon& poly) {
  int n = static_cast<int>(poly.size());
  double res = 0;
  for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
    for (;; j = ((j + 1) % n)) {
      res = max(res, abs(poly[i] - poly[j]));
      if (ccw(poly[i+1] - poly[i], 
        poly[((j + 1) % n)] - poly[j]) >= 0) break;
    }
  return res; }
// vim: cc=60 ts=2 sts=2 sw=2:
