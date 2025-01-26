echo "#### time-test-facility Run ####"
echo

if [ "$(dirname "$0")" != "./install" ]; then
  echo "  Please run this script from the root directory"
  exit 1
fi

echo "Running C++ benchmarking"
echo
./ttf-build/main

echo "-----------------"

echo "Running Python benchmarking"
echo
python3 ./ttf-build/main.py 2>/dev/null || python ./ttf-build/main.py

echo
echo "#### time-test-facility Run ####"

exit 0
