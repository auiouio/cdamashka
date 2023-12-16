#include <algorithm>
#include <cassert>



template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    class GridRow {
    private:
        T* const rowData;

    public:
        GridRow(T* rowData) : rowData(rowData) {}

        T& operator[](size_type idx) {
            return rowData[idx];
        }

        const T& operator[](size_type idx) const {
            return rowData[idx];
        }
    };

    T *const data;
    size_type const y_size, x_size;

public:
    Grid(T *data, size_type y_size, size_type x_size) :
        data(data), y_size(y_size), x_size(x_size) {}

    Grid(Grid<T> const &) = delete;
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;


    Grid(T const &t) : data(new T[1]), y_size(1), x_size(1) {
        data[0] = t;
    }

    Grid(size_type y_size, size_type x_size) :
        data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {}

    Grid(size_type y_size, size_type x_size, T const &t) :
        data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {
        std::fill(data, data + y_size * x_size, t);
    }

    ~Grid() {
        delete[] data;
    }


    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const &t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    GridRow operator[](size_type idx) {
        return GridRow(data + idx * x_size);
    }

    const GridRow operator[](size_type idx) const {
        return GridRow(data + idx * x_size);
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};


int main() {
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g[y_idx][x_idx]);

    return 0;
}
