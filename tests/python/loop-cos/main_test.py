import math
import unittest
import random
from ..main import fast_cos


class TestFastCos(unittest.TestCase):
    def test_basic_angles(self):
        test_cases = [
            (0, 1.0),
            (math.pi/2, 0.0),
            (math.pi, -1.0),
            (3*math.pi/2, 0.0),
            (2*math.pi, 1.0)
        ]
        for x, expected in test_cases:
            with self.subTest(x=x):
                self.assertAlmostEqual(fast_cos(x), expected, places=12)

    def test_random_values(self):
        for _ in range(1000):
            x = random.uniform(-1000, 1000)
            with self.subTest(x=x):
                actual = fast_cos(x)
                expected = math.cos(x)
                self.assertAlmostEqual(actual, expected, delta=1e-12)

    def test_special_cases(self):
        # Проверка точности в критических точках
        self.assertAlmostEqual(fast_cos(math.pi/3), 0.5, places=14)
        self.assertAlmostEqual(fast_cos(math.pi/4), math.sqrt(2)/2, places=14)
        self.assertAlmostEqual(fast_cos(math.pi/6), math.sqrt(3)/2, places=14)

    def test_large_arguments(self):
        large_values = [1e6, -1e7, 2e8, 9.999999999999999e+15]
        for x in large_values:
            with self.subTest(x=x):
                self.assertAlmostEqual(fast_cos(x), math.cos(x), delta=1e-12)

    def test_precision(self):
        # Проверка максимальной абсолютной ошибки
        max_error = 0.0
        for _ in range(10000):
            x = random.uniform(0, 2*math.pi)
            error = abs(fast_cos(x) - math.cos(x))
            max_error = max(max_error, error)
        self.assertLessEqual(max_error, 1e-12)


if __name__ == '__main__':
    unittest.main()
