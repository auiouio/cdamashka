#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void hb(int* ptr, size_t N) {
    for (int i = 0; i < N; i ++) {
        if (ptr[i] > ptr[i+N/4]) {
            swap(ptr[i], ptr[i+1]);
        }
    }
}

void bubble_sort(int* ptr, size_t N) {
    int i = 0;
    while (i < N) {
        if (i == 0)
            i++;
        if (ptr[i] >= ptr[i - 1])
            i++;
        else {
            swap(ptr[i], ptr[i - 1]);
            i--;
        }
    }
    return;
}

void randomize(int* ptr, size_t N, int seed) {
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, N);
    for (int i = 0; i < N; i++)
    {
        ptr[i] = dstr(rng);
        i++;
    }
}

void create_outfile(double* ptr, size_t N, int step) {
    std::ofstream out("linsearch_extratime.csv", std::ios::out);
    for (int i = 0; i < N; ++i) {
        if (out.is_open()) {
            out << step * (i + 1) << "," << ptr[i] << endl;
        }
    }
    out.close();
}

int main() {
    int* data = nullptr;  // массив данных
    double* ans = nullptr;  // массив усредненных времен для каждого эксперимента
    int time1 = 0;
    for (int N = 100; N < 100000; N += 100) {
        ans = new double[1000];
        for (int repeats = 0; repeats < 100; ++repeats) {
            data = new int[N];
            randomize(data, N, 1001); 
            hb(data, N);
            auto begin = std::chrono::steady_clock::now();
            bubble_sort(data, N);
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
            time1 += time_span.count();
            delete[] data;
        }
        *(ans+ N/100 - 1) = time1;
    }
    create_outfile(ans, 999, 100);
    delete [] ans;
    return 0;
}
