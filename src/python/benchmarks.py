from concurrent.futures.thread import ThreadPoolExecutor
import time
import math
import numpy as np
from functools import wraps
from concurrent.futures import ProcessPoolExecutor
import hashlib
import os
import pickle


def benchmark(func):
    """Improved benchmarking decorator with error handling"""
    test_name = ' '.join([word.title()
                         for word in func.__name__.split('_')]) + " Test"

    @wraps(func)
    def wrapper(*args, **kwargs):
        try:
            start = time.perf_counter_ns()
            result = func(*args, **kwargs)
            duration = (time.perf_counter_ns() - start) * 1e-9
            print(f"{test_name:<35} | {duration:.6f} sec |")
            return result
        except Exception as e:
            print(f"{test_name:<35} | ERROR: {str(e)[:50]} |")
            return None
    return wrapper


@benchmark
def matrix_operations(scale=10):
    """High-dimensional matrix computations"""
    a = np.random.rand(1000 * scale, 1000)
    b = np.random.rand(1000, 1000 * scale)
    return np.dot(a, b)


@benchmark
def recursive_fibonacci():
    """Deep recursion performance"""
    def fib(n):
        return fib(n-1) + fib(n-2) if n > 1 else n
    return fib(35)


@benchmark
def memory_intensive_task():
    """Optimized memory handling"""
    data = (
        tuple(zip([f"key_{i}" for i in range(100)],
                  [os.urandom(1024)] * 100))
        for _ in range(10000)
    )
    return sum(len(str(item)) for item in data)


@benchmark
def cryptographic_hash():
    """Cryptographic operations"""
    data = os.urandom(10000000)
    return hashlib.sha512(data).hexdigest()


def prime_check(n):
    """Helper function for parallel processing"""
    if n < 2:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


@benchmark
def parallel_processing():
    """Fixed multiprocessing implementation"""
    with ProcessPoolExecutor() as executor:
        numbers = range(2_000_000, 2_001_000)
        return sum(executor.map(prime_check, numbers))


@benchmark
def thread_pool_io():
    """Thread pool for simulated I/O operations"""
    def fake_io(_):
        time.sleep(0.001)
        return math.sqrt(_)

    with ThreadPoolExecutor() as executor:
        return list(executor.map(fake_io, range(5000)))


@benchmark
def generator_expression():
    """Large-scale generator pipeline"""
    return sum((x**2 for x in range(10**7) if x % 3 == 0))


@benchmark
def object_serialization():
    """Complex object serialization/deserialization"""
    data = [{"matrix": np.random.rand(100, 100),
            "hash": hashlib.md5(os.urandom(128)).digest()}
            for _ in range(5000)]
    serialized = pickle.dumps(data)
    return len(pickle.loads(serialized))


@benchmark
def string_pattern_matching():
    """Regex pattern matching performance"""
    import re
    text = "".join([f"{i}abc{'xyz' * (i % 5)}" for i in range(100000)])
    return len(re.findall(r"\d+xyz{3}", text))
