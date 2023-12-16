#include <vector>
#include <cassert>
#include <iostream>


// Forward declaration
template <typename T, unsigned D>
class Grid;

// Specialization for 1-dimensional grid
template <typename T>
class Grid<T, 1> {
    std::vector<T> data;

public:
    Grid(size_t size, T const& value = T{}) : data(size, value) {}

    T& operator()(size_t i) {
        return data[i];
    }

    const T& operator()(size_t i) const {
        return data[i];
    }

    T& operator[](size_t i) {
        return data[i];
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    size_t size() const {
        return data.size();
    }
};

// General template for N-dimensional grid
template <typename T, unsigned D>
class Grid {
    std::vector<Grid<T, D - 1>> data;

public:
    Grid() = default;

    template <typename... Dimensions>
    Grid(size_t firstDim, Dimensions... otherDims) : data(firstDim, Grid<T, D - 1>(otherDims...)) {}

    Grid<T, D - 1>& operator[](size_t i) {
        return data[i];
    }

    const Grid<T, D - 1>& operator[](size_t i) const {
        return data[i];
    }

    template <typename... Dimensions>
    T& operator()(size_t firstDim, Dimensions... otherDims) {
        return data[firstDim](otherDims...);
    }

    template <typename... Dimensions>
    const T& operator()(size_t firstDim, Dimensions... otherDims) const {
        return data[firstDim](otherDims...);
    }

    size_t size() const {
        return data.size();
    }
};

int main() {
    Grid<float, 3> g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    g3[1][1][1] = 2;
    assert(2.0f == g3(1, 1, 1));

    std::cout << "Test done!\n";
    return 0;
}