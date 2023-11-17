#include <iostream>
#include <vector>
#include "C:\Users\auiod\cdamashka\cdamashka\first\include\my_library.h"
#include <algorithm>

template <typename T, typename Comparator = std::less<T>>
class PriorityQueue {
    private:
    std::vector<T> a;
    
    Comparator comp;

    void Up(int i) {
        while (i != 0 && comp(a[(i-1)/2], a[i])) {
            i = (i-1)/2;
        }
    }

    void Down(int i) {
        while (2*i -1 < a.size()) {
            int MaxChild = 2*i + 1;
            if (MaxChild +1 < a.size() && comp(a[MaxChild],a[MaxChild+1])) {
                MaxChild++;
            };
            if (!comp(a[i],a[MaxChild])) {
                break;
            };
            std::swap(a[i], a[MaxChild]);
            i = MaxChild;
        }
    }
    public:

    // Конструктор по умолчанию
    PriorityQueue() {}

    // Добавляет элемент в очередь
    void Push(int value) {
        a.push_back(value);
        Up(a.size() - 1);
    }

    // Удаляет верхний элемент
    T poll() {
        T value = a[0];
        a[0] = a[a.size() - 1];
        a.pop_back();
        Down(0);
        return value;
    }

    // Возвращает вехний элемент
    T peek() {
        return a[0];
    }

    // Проверяет пустая ли очередь
    bool IsEmpty() {
        return a.empty();
    }

    // Освобождает память
    void Free() {
        a.clear();
    }
};