import benchmarks

if __name__ == "__main__":
    @benchmarks.benchmark
    def total():
        benchmarks.matrix_operations(scale=3)
        benchmarks.recursive_fibonacci()
        benchmarks.memory_intensive_task()
        benchmarks.cryptographic_hash()
        benchmarks.parallel_processing()
        benchmarks.thread_pool_io()
        benchmarks.generator_expression()
        benchmarks.object_serialization()
        benchmarks.string_pattern_matching()
        print()

    total()
