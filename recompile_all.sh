rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release #Debug
make -j$(nproc)

cd ../hashtest
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release #Debug
make -j$(nproc)
