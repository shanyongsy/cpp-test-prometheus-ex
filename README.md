# cpp-test-prometheus

## build prometheus-cpp-dev lib
### code
- from https://github.com/jupp0r/prometheus-cpp/tree/v1.1.0
### build sdk lib
use https://github.com/shanyongsy/cpp-test-prometheus-ex/blob/master/common/lib/prometheus/build_prometheus_cpp_dev_lib.sh
## build test code
### build 32bit
```
mkdir _build
cd _build
"Modify CMakeLists.txt for 32bit or 64bit"
cmake ..
make
```
### run
```
./main -p 8080
```
### test
http://127.0.0.1:8080/metrics

