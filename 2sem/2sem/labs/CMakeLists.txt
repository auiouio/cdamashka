
project(2sem)
add_executable("labs" "grid.cpp")
add_executable("labs" "SkipList.cpp")
add_executable("labs" "ndgrid.cpp")

```
Команды для старта из консоли (не зависят от ide)
```
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```