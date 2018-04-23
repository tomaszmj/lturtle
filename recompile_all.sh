rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. # will be changed to release
make -j$(nproc)

cd ../hashtest
rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. # will be changed to release
make -j$(nproc)
