#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;
    T *  data; 
    size_type const y_size, x_size; 

    Grid(T *data, size_type y_size, size_type x_size):
        data(data), y_size(y_size), x_size(x_size) { }

    Grid(Grid<T> const &) = delete; //копирование
    Grid (Grid<T>&&) = delete; // перемещение
    Grid<T>& operator=(Grid<T>&) = delete; // присваивание копирования
    Grid<T>& operator=(Grid<T>&&) = delete; // перемещения

    T operator ()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator ()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const &t) {
        for (
        auto it = data, end = data + x_size * y_size;
        it != end; ++it
        ) *it = t;
        return *this;
    }

    // Создаем сетку из одного элемента t
    Grid(T const &t): data(new T[1]), x_size(1), y_size(1) {
        data[0] = t;
    };

    // Создаем сетку размера y_size на x_size с элементами, созданными конструктором по умолчанию
    Grid(size_type y_size, size_type x_size): x_size(x_size), y_size(y_size) {
        data = new T[y_size*x_size]();
    }

    // То же, что выше, но теперь заполняем сетку элементами  t
    Grid(size_type y_size, size_type x_size, T const &t): x_size(x_size), y_size(y_size) {
        data = new T[y_size * x_size];
        std::fill_n(data, y_size * x_size, t);
    }

    //оператор для доступа к строке
    T *operator[](size_type y) {
        assert(y < y_size && "Index out of bounds");
        return data + y * x_size;
    }

    // для константного доступа
    const T *operator[](size_type y) const {
        assert(y < y_size && "Index out of bounds");
        return data + y * x_size;
    }
    
    ~Grid() {
    delete[] data;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};

template <typename T, int dim>
class NDGrid {
    public:
    using value_type = T;
    using size_type = unsigned;
    T *  data; 
    size_type Flattered;

    size_type Dimensions[dim]; 

    NDGrid(T *data, size_type *Dimensions):
        data(data), Dimensions(Dimensions) { 
            for (int i = 0; i < dim; i++) {
            Flattered *= Dimensions[i];
        }
    }
    
    NDGrid(NDGrid<T, dim> const &) = delete; //копирование
    NDGrid (NDGrid<T, dim>&&) = delete; // перемещение
    NDGrid<T, dim>& operator=(NDGrid<T, dim>&) = delete; // присваивание копирования
    NDGrid<T, dim>& operator=(NDGrid<T, dim>&&) = delete; // перемещения

    T operator()(const size_type* indices) const {
        size_type flatIndex = 0;
        size_type multiplier = 1;

        for (int i = 0; i < dim; ++i) {
            flatIndex += indices[i] * multiplier;
            multiplier *= Dimensions[i];
        }

        return data[flatIndex];
    }
    T& operator()(const size_type* indices) {
        size_type flatIndex = 0;
        size_type multiplier = 1;

        for (int i = 0; i < dim; ++i) {
            flatIndex += indices[i] * multiplier;
            multiplier *= Dimensions[i];
        }

        return data[flatIndex];
    }

    NDGrid<T, dim>& operator=(T const &t) {
        
        for (auto it = data, end = data + Flattered;
            it != end; ++it
            ) *it = t;
        return *this;
    }
};

int main() {
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert (0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert (1.0f == g[y_idx][x_idx]);
    return 0;
}