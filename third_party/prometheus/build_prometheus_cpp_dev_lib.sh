#code from https://github.com/jupp0r/prometheus-cpp/releases/tag/v1.1.0
git clone --branch v1.1.0 git@github.com:jupp0r/prometheus-cpp.git

cd prometheus-cpp

#fetch third-party dependencies
git submodule init
git submodule update

#make a build directory
mkdir _build_x86
cd _build_x86

#run cmake
cmake .. -DBUILD_SHARED_LIBS=OFF -DENABLE_PUSH=OFF -DENABLE_COMPRESSION=OFF -DCMAKE_INSTALL_PREFIX="../../install_x86" -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32

#build
cmake --build . --parallel 4

#install the libraries and headers
cmake --install .

echo "Done building prometheus-cpp-x86. You can find the libraries and headers in the install_x86 directory."

cd ..
mkdir _build_x86_64
cd _build_x86_64

#run cmake
cmake .. -DBUILD_SHARED_LIBS=OFF -DENABLE_PUSH=OFF -DENABLE_COMPRESSION=OFF -DCMAKE_INSTALL_PREFIX="../../install_x86_64" -DCMAKE_C_FLAGS=-m64 -DCMAKE_CXX_FLAGS=-m64

#build
cmake --build . --parallel 4

#install the libraries and headers
cmake --install .

cd ../..
rm -rf prometheus-cpp

echo "Done building prometheus-cpp-x86. You can find the libraries and headers in the install_x86 directory."
echo "Done building prometheus-cpp-x86_64. You can find the libraries and headers in the install_x86_64 directory."
