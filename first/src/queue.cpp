#include <iostream>
#include <vector>
#include "C:\Users\auiod\cdamashka\cdamashka\first\include\my_library.h"
#include <algorithm>
#include <utility>  // Для std::pair

template <typename T, typename Priority = int, typename Comparator = IntComparator>
class PriorityQueue {
private:
    std::vector<std::pair<T, Priority>> a;
    Comparator comp;

    void Up(int i) {
        while (i != 0 && comp(a[(i - 1) / 2].second, a[i].second)) {
            std::swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void Down(int i) {
        while (2 * i + 1 < a.size()) {
            int maxChild = 2 * i + 1;
            if (maxChild + 1 < a.size() && comp(a[maxChild].second, a[maxChild + 1].second)) {
                maxChild++;
            }
            if (!comp(a[i].second, a[maxChild].second)) {
                break;
            }
            std::swap(a[i], a[maxChild]);
            i = maxChild;
        }
    }

public:
    // Конструктор по умолчанию
    PriorityQueue() {}

    // Добавляет элемент в очередь с приоритетом
    void Push(const T& value, const Priority& priority) {
        a.emplace_back(value, priority);
        Up(a.size() - 1);
    }

    // Удаляет верхний элемент
    T Poll() {
        if (IsEmpty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }

        T value = a[0].first;
        a[0] = a[a.size() - 1];
        a.pop_back();
        Down(0);
        return value;
    }

    // Возвращает верхний элемент
    T Peek() const {
        if (IsEmpty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        return a[0].first;
    }

    // Проверяет, пуста ли очередь
    bool IsEmpty() const {
        return a.empty();
    }
};

int main() {
    PriorityQueue<std::string, int, IntComparator> priorityQueue_em;

    if (priorityQueue_em.IsEmpty()) {
        std::cout<< "Очередь пустая" << std::endl;
    };

    PriorityQueue<std::string, int, IntComparator> priorityQueue;

    priorityQueue.Push("Task 1", 2);
    priorityQueue.Push("Task 2", 1);
    priorityQueue.Push("Task 3", 3);

    while (!priorityQueue.IsEmpty()) {
        std::cout << priorityQueue.Poll() << std::endl;
    }

    PriorityQueue<std::string, int, IntComparator> priorityQueue_em;
    if (priorityQueue_em.IsEmpty()) {
        std::cout<< "Очередь пустая" << std::endl;
    };
    return 0;
}