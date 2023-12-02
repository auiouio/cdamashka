#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cstdarg>
#include <tuple>

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
private:
    template<typename... Indices>
    size_t calculateFlatIndex(Indices... indices) const {
        size_t flatIndex = 0;
        size_t multiplier = 1;

        std::vector<int> IndexArr = {indices...};

        for (int i = 0; i < sizeof...(indices); ++i) {
            assert(IndexArr[i] < Dimensions[i] && "Index out of bounds");
            flatIndex += IndexArr[i] * multiplier;
            if (i < Dimensions.size() - 1) {
                multiplier *= Dimensions[i];
            }
        }

        return flatIndex;
    }



public:
    using value_type = T;
    using size_type = unsigned;

    T *data;
    size_type Flattered;
    std::vector<size_type> Dimensions;

    NDGrid(T *data, size_type *dimensions)
        : data(data), Dimensions(dimensions), Flattered(1) {
        for (int i = 0; i < dim; i++) {
            Flattered *= Dimensions[i];
        }
    }
    //N-мерная сетка из одного элемента t
    NDGrid(T const &t, size_type dimensions, ...): data(new T[1]), Flattered(1) {
        data[0] = t;

        va_list args;
        va_start(args, dimensions);
        for (int i = 0; i < dimensions; i++) {
            Dimensions.push_back(va_arg(args, size_type));
            Flattered *= Dimensions[i];  
        }
        va_end(args);
    }


    // Создаем сетку размера y_size на x_size с элементами, созданными конструктором по умолчанию
    NDGrid(size_t dimensions, ...) {
        va_list args;
        va_start(args, dimensions);
        for (int i = 0; i < dimensions; i++) {
            Dimensions.push_back(va_arg(args, size_t));
        }
        va_end(args);
        data = new T[Flattered]();
    }

    // То же, что выше, но теперь заполняем сетку элементами  t
    template <typename... Dimensions_tuple>
    NDGrid(Dimensions_tuple... dims, T const &t) : Dimensions({static_cast<size_type>(dims)...}), data(nullptr) {
        size_type Flattened = std::apply([](auto... args) { return (args * ...); }, Dimensions);
        data = new T[Flattened];
        std::fill_n(data, Flattened, t);
    }

    template<typename... Indices>
    T& operator()(Indices... indices) const {
        size_type flatIndex = calculateFlatIndex(indices...);

        return data[flatIndex];
    }

    // Оператор для доступа к слою
    T* operator[](size_type index) const {
        assert(index < Dimensions[dim - 1] && "Index out of bounds");

        size_type sliceSize = Flattered / Dimensions[dim - 1];
        return &data[index * sliceSize];
    }


    // Оператор присваивания
    NDGrid& operator=(const T* other) {
        // Здесь следует учесть, что другой массив other должен быть той же размерности
        // и соответствовать ожидаемым размерам исходного объекта.

        // копирование данных
        std::copy(other, other + Flattered, data);

        return *this;
    }




    ~NDGrid() {
        delete[] data;
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


    NDGrid<float,2> g2(2, 5, 2.0f);
    assert (2.0f == g2(1, 1));
    NDGrid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));
    return 0;
}