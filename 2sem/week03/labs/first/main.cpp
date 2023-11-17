#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


template <typename T>
struct Comparator {
    virtual bool operator()(T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int> {
    bool operator()(int const& lha, int const& rha) const override {
        return lha < rha;
    }
};

template <typename T>
int Partition(std::vector<T>& a, const Comparator<T>& comp, int start, int end) {
    T pivot = a[end];
    int index = start;
    for (int i = start; comp(i, end); i++) {
        if (!comp(pivot, a[i])) {
            std::swap(a[i], a[index]);
            index++;
        }
    }
    std::swap(a[index], a[end]);
    return index;
}

template <typename T>
void QuickSort(std::vector<T>& a, const Comparator<T>& comp, int start, int end) {
    if (start >= end) {
        return;
    }

    int pivot = Partition(a, comp, start, end);

    QuickSort(a, comp, start, pivot - 1);

    QuickSort(a, comp, pivot + 1, end);
}

template <typename T>
void Test(std::vector<T>& a, const Comparator<T>& comp) {
    int end = a.size();
    for (int j = 0; j < end; j++) {
        for (int i = j; i < end; i++) {
            if (comp(a[i], a[j])) {
                std::cout << "Тест не прошел" << std::endl;
            }
        }
    }
}

int main() {
    std::vector<int> a(10, 0);

    IntComparator intComparator;

    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> dstr(0, 9);

    for (unsigned counter = 100; counter != 0; --counter) {
        a[dstr(rng)] = std::rand() % 100;
    }

    std::cout << "Vector elements: ";
    for (const auto& element : a) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    QuickSort(a, intComparator, 0, a.size() - 1);

    std::cout << "Sorted vector: ";
    for (const auto& element : a) {
        std::cout << element << " ";
    }

    return 0;
}
