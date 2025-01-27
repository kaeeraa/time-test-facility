#!/bin/bash
START=$(date +%s)

echo "#### time-test-facility Build ####"
echo
if [ "$(dirname "$0")" != "./install" ]; then
  echo "  Please run this script from the root directory"
  exit 1
fi

echo "  Working directory: $(pwd)"

rm -rf build/
cmake -B build -DCMAKE_BUILD_TYPE=Debug || error=1
cmake --build build || error=1
echo
echo "#### time-test-facility Build ####"

END=$(date +%s)
DIFF=$(($END - $START))

echo
echo "Build took $DIFF seconds"

if [ -n "$error" ]; then
  exit 1
fi
