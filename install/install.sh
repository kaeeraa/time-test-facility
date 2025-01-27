#!/bin/bash
START=$(date +%s)
echo "#### time-test-facility Install ####"
echo

if [ "$(dirname "$0")" != "./install" ]; then
  echo "  Please run this script from the root directory"
  exit 1
fi

echo "  Working directory: $(pwd)"

echo "  Creating ttf-build directory"
mkdir -p ttf-build

echo "  Hard-linking builds"

linked_count=0

if cp -lf build/main ttf-build/main; then
  linked_count=$((linked_count + 1))
else
  echo "  C++ binary not found"
  error=1
fi

if cp -lf src/python/benchmarks.py ttf-build/benchmarks.py; then
  linked_count=$((linked_count + 1))
else
  echo "  Python benchmarks not found"
  error=1
fi

if cp -lf src/python/main.py ttf-build/main.py; then
  linked_count=$((linked_count + 1))
else
  echo "  Python main module not found"
  error=1
fi

chmod +x ttf-build/main

echo
echo "  Linked $linked_count files"
echo

echo "#### time-test-facility Install ####"

END=$(date +%s)
DIFF=$(($END - $START))

echo
echo "Install took $DIFF seconds"

if [ -n "$error" ]; then
  exit 1
fi
