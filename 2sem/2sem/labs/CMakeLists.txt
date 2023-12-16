
project(labs)
add_executable("lab11" "src/grid.cpp")
add_executable("lab2" "src/SkipList.cpp")
add_executable("lab12" "src/ndgrid.cpp")

```
Команды для старта из консоли (не зависят от ide)
```
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```