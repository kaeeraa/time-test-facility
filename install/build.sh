#!/bin/bash
START=$(date +%s)

echo "#### time-test-facility Build ####"
echo
if [ "$(dirname "$0")" != "./install" ]; then
  echo "  Please run this script from the root directory"
  exit 1
fi
rm -rf build/
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
echo
echo "#### time-test-facility Build ####"

END=$(date +%s)
DIFF=$(($END - $START))

echo
echo "Build took $DIFF seconds"

exit 0
