#include <chrono>
#include <cmath>
#include <cstring>
#include <future>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <random>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

// Benchmarking macro
#define BENCHMARK(func)                                                        \
  do {                                                                         \
    auto start = high_resolution_clock::now();                                 \
    func();                                                                    \
    auto duration =                                                            \
        duration_cast<nanoseconds>(high_resolution_clock::now() - start)       \
            .count() *                                                         \
        1e-9;                                                                  \
    cout << #func << " Test" << string(30 - strlen(#func), ' ') << " | "       \
         << fixed << duration << " sec |" << endl;                             \
  } while (0)

// 1. Matrix Operations (naive implementation)
void matrix_operations() {
  const int size = 1000;
  vector<vector<double>> a(size, vector<double>(size));
  vector<vector<double>> b(size, vector<double>(size));
  vector<vector<double>> c(size, vector<double>(size));

  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      a[i][j] = dis(gen);
      b[i][j] = dis(gen);
    }
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < size; ++k) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// 2. Recursive Fibonacci
int fib(int n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }
void recursive_fibonacci() {
  volatile int r = fib(35);
  (void)r;
}

// 3. Memory Intensive Task
void memory_intensive_task() {
  struct Data {
    array<string, 100> keys;
    array<array<char, 1024>, 100> values;
  };

  vector<Data> data(10000);
  volatile size_t total = 0;
  for (const auto &item : data) {
    total += item.keys.size() + item.values.size();
  }
}

// 4. Cryptographic Hash (SHA512)
void cryptographic_hash() {
  vector<uint8_t> data(10'000'000);
  generate(data.begin(), data.end(), mt19937{random_device{}()});

  SHA512_CTX ctx;
  SHA512_Init(&ctx);
  SHA512_Update(&ctx, data.data(), data.size());
  array<uint8_t, SHA512_DIGEST_LENGTH> digest;
  SHA512_Final(digest.data(), &ctx);
}

// 5. Parallel Processing
bool is_prime(int n) {
  if (n < 2)
    return false;
  for (int i = 2; i * i <= n; ++i)
    if (n % i == 0)
      return false;
  return true;
}

void parallel_processing() {
  vector<future<bool>> futures;
  for (int i = 2'000'000; i < 2'001'000; ++i)
    futures.emplace_back(async(launch::async, is_prime, i));

  volatile int count = 0;
  for (auto &f : futures)
    count += f.get();
}

// 6. Thread Pool IO
void thread_pool_io() {
  auto fake_io = [](int i) {
    this_thread::sleep_for(1ms);
    return sqrt(i);
  };

  vector<future<double>> futures;
  for (int i = 0; i < 5000; ++i)
    futures.emplace_back(async(launch::async, fake_io, i));

  volatile double sum = 0;
  for (auto &f : futures)
    sum += f.get();
}

// 7. Generator Expression
void generator_expression() {
  volatile long long sum = 0;
  for (int x = 0; x < 10'000'000; ++x) {
    if (x % 3 == 0)
      sum += x * x;
  }
}

// 8. Object Serialization (simple implementation)
struct Serializable {
  vector<double> data;
  string info;

  string serialize() const {
    ostringstream oss;
    for (auto v : data)
      oss << v << " ";
    oss << "|" << info;
    return oss.str();
  }
};

void object_serialization() {
  vector<Serializable> data(5000);
  for (auto &item : data) {
    item.data.resize(100);
    item.info = "test_string";
  }

  volatile size_t total = 0;
  for (const auto &item : data) {
    total += item.serialize().size();
  }
}

// 9. String Pattern Matching
void string_pattern_matching() {
  string text;
  for (int i = 0; i < 100'000; ++i) {
    text += to_string(i) + "abc" + string(i % 5, 'x');
  }

  regex pattern(R"(\d+xxx)");
  sregex_iterator it(text.begin(), text.end(), pattern);
  volatile size_t count = distance(it, sregex_iterator());
}

int main() {
  auto start = chrono::high_resolution_clock::now();
  BENCHMARK(matrix_operations);
  BENCHMARK(recursive_fibonacci);
  BENCHMARK(memory_intensive_task);
  BENCHMARK(cryptographic_hash);
  BENCHMARK(parallel_processing);
  BENCHMARK(thread_pool_io);
  BENCHMARK(generator_expression);
  BENCHMARK(object_serialization);
  BENCHMARK(string_pattern_matching);
  auto end = chrono::high_resolution_clock::now();
  auto total =
      chrono::duration_cast<chrono::duration<double>>(end - start).count();
  cout << std::setprecision(6) << fixed;
  cout << "\nTotal Test                          | " << total << " sec" << " |"
       << endl;

  return 0;
}