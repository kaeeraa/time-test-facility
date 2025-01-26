#include <array>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

double fast_cos(double x) {
  // Argument reduction using periodicity and even function property
  x = std::abs(x);          // cos(x) = cos(-x)
  x = std::fmod(x, 2 * PI); // Reduce to [0, 2π)

  // Mirror reduction to [0, π]
  if (x > PI) {
    x = 2 * PI - x;
  }

  // Quadrant reduction to [0, π/2]
  int sign = 1;
  if (x > PI / 2) {
    x = PI - x;
    sign = -1;
  }

  // Precompute x² for polynomial evaluation
  const double x2 = x * x;

  // Precalculated Taylor series coefficients 1/(2n)!
  // Up to x^20/20! term
  constexpr std::array<double, 10> coeffs = {
      -0.5,                    // -1/(2!)
      0.041666666666666664,    // 1/(4!)
      -0.001388888888888889,   // -1/(6!)
      2.48015873015873e-5,     // 1/(8!)
      -2.7557319223985893e-7,  // -1/(10!)
      2.08767569878681e-9,     // 1/(12!)
      -1.1470745597729725e-11, // -1/(14!)
      4.779477332387385e-14,   // 1/(16!)
      -1.5619206968586225e-16, // -1/(18!)
      4.110317623312165e-19    // 1/(20!)
  };

  // Horner's method for polynomial evaluation
  double result = 0.0;
  for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it) {
    result = result * x2 + *it;
  }

  // Final calculation with initial 1.0
  return sign * (result * x2 + 1.0);
}

int main() {
  for (int i = 0; i < 100000; ++i) {
    fast_cos(i);
  }

  return 0;
}