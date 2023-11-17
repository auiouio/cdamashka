#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

template <typename T>


struct Comparator {
    virtual bool operator()(T const &, T const &) const = 0;
};

struct IntComparator final: Comparator<int> {
    bool operator()(int const &lha, int const &rha) const override {
        return lha < rha;
    }
};

template <typename T>
int Partition(std::vector<T>& a, const Comparator<T>& comp, int start, int end) {
    T pivot = a[start];
    int index = end;
    for (int i = end; comp(i, start); i--) {
        if (!comp(a[i], pivot))
        {
            std::swap(a[i], a[index]);
            index++;
        }
    }
    return index;
}

template <typename T>
void QuickSort(std::vector<T>& a, const Comparator<T>& comp, int start, int end) {
    IntComparator intComparator;
    if (!comp(start, end)) {
        return;
    }
    int pivot = Partition(a, intComparator, start, end);
 
    QuickSort(a, intComparator, start, pivot - 1);
 
    QuickSort(a, intComparator, pivot + 1, end);
}

template <typename T>
void Test(std::vector<T>& a, const Comparator<T>& comp) {
    int end = a.size();
    for (int j = 0; j<end; j++) {
        for (int i = j; i<end; i++) {
            if (comp(a[i], a[j])) {
                std::cout << "Тест не прошел" << std::endl;
            }
        }
    };
}


int main() {
    std::vector<int> a(10, 0);

    IntComparator intComparator;

    unsigned seed = 1001;
    std::default_random_engine rng(seed );
    std::uniform_int_distribution<unsigned> dstr (0,9);

    for (unsigned counter = 100; counter != 0; --counter)  {
        a[dstr(rng)] = std::rand() %100;
        }
    std::cout << "Vector elements: ";
    for (const auto& element : a) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    QuickSort(a, intComparator, 0, a.size()-1);
    for (const auto& element : a) {
        std::cout << element << " ";
    }

    return 0;
}
