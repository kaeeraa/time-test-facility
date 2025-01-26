"""Loop-based cosine experiment."""
import math
from numba import njit


@njit(fastmath=True)
def fast_cos(x):
    """
    Compute the cosine of x (in radians) efficiently using argument reduction and Taylor series.

    Args:
        x (float): Input angle in radians.

    Returns:
        float: Cosine of x.
    """
    # Reduce x to [0, 2π) range using periodicity and even property
    x = abs(x)  # cos(x) = cos(-x)
    x = x % (2 * math.pi)  # x in [0, 2π)

    # Reduce to [0, π] using cos(x) = cos(2π - x)
    if x > math.pi:
        x = 2 * math.pi - x

    # Reduce to [0, π/2] using cos(x) = -cos(π - x)
    if x > math.pi / 2:
        x = math.pi - x
        sign = -1
    else:
        sign = 1

    # Precompute x² for Horner's method
    x_squared = x * x

    # Precomputed coefficients for cos(x) Taylor series up to x^20/20!
    coeffs = (
        -0.5,                    # -1/(2!)
        0.041666666666666664,    # 1/(4!)
        -0.001388888888888889,   # -1/(6!)
        2.48015873015873e-5,     # 1/(8!)
        -2.7557319223985893e-7,  # -1/(10!)
        2.08767569878681e-9,     # 1/(12!)
        -1.1470745597729725e-11,  # -1/(14!)
        4.779477332387385e-14,   # 1/(16!)
        -1.5619206968586225e-16,  # -1/(18!)
        4.110317623312165e-19    # 1/(20!)
    )

    # Evaluate polynomial using Horner's method
    result = 0.0
    for coeff in reversed(coeffs):
        result = result * x_squared + coeff

    # Finalize computation: result = 1 + x²*(a0 + x²*(a1 + ...))
    result = result * x_squared + 1.0

    return sign * result


if __name__ == "__main__":
    for i in range(100000):
        fast_cos(i)
