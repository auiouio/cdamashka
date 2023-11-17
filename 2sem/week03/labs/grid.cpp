#include <iostream>

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T * const data; 
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

    Grid(T const &t): data(new T[1]), x_size(1), y_size(1) {
        data[0] = t;
    };

    Grid(size_type y_size, size_type x_size): x_size(x_size), y_size(y_size) {
        data = new T[y_size*x_size]();
    }

    Grid(size_type y_size, size_type x_size, T const &t): x_size(x_size), y_size(y_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
    }

    // Оператор присваивания перемещения
    Grid<T>& operator=(Grid<T>&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    // Перемещающий конструктор
    Grid(Grid<T>&& other) : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }
    
    ~Grid() {
    delete[] data;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};