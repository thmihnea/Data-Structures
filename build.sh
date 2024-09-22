rm -rf build
mkdir build
cd build

cmake ..
make
echo "Running program."
cd target
./data-structures