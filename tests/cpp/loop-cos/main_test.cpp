#include <cmath>
#include 

constexpr double PI = 3.14159265358979323846;

TEST(FastCosTest, BasicAngles) {
  EXPECT_NEAR(fast_cos(0), 1.0, 1e-12);
  EXPECT_NEAR(fast_cos(PI / 2), 0.0, 1e-12);
  EXPECT_NEAR(fast_cos(PI), -1.0, 1e-12);
  EXPECT_NEAR(fast_cos(3 * PI / 2), 0.0, 1e-12);
  EXPECT_NEAR(fast_cos(2 * PI), 1.0, 1e-12);
}

TEST(FastCosTest, SpecialValues) {
  EXPECT_NEAR(fast_cos(PI / 3), 0.5, 1e-12);
  EXPECT_NEAR(fast_cos(PI / 4), sqrt(2) / 2, 1e-12);
  EXPECT_NEAR(fast_cos(PI / 6), sqrt(3) / 2, 1e-12);
}

TEST(FastCosTest, LargeArguments) {
  for (double x : {1e6, -1e7, 2e8, 1e16}) {
    EXPECT_NEAR(fast_cos(x), cos(x), 1e-12);
  }
}

TEST(FastCosTest, Precision) {
  constexpr int N = 10000;
  double max_error = 0.0;
  std::mt19937_64 rng;
  std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

  for (int i = 0; i < N; ++i) {
    double x = dist(rng);
    double error = std::abs(fast_cos(x) - std::cos(x));
    max_error = std::max(max_error, error);
  }

  EXPECT_LT(max_error, 1e-12);
}

TEST(FastCosTest, Randomized) {
  std::mt19937_64 rng;
  std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

  for (int i = 0; i < 1000; ++i) {
    double x = dist(rng);
    EXPECT_NEAR(fast_cos(x), std::cos(x), 1e-12);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}