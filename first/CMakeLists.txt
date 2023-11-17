project(first)
add_executable("src" "sort.cpp" "queue.cpp")

cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
