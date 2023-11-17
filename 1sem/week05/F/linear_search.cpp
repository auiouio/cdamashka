#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;

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

void finder(int* ptr, int N) {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(N+1, 2*N);
    int b = dstr(rng);
    int i = 0;
    for (int i = 0; i<N; i++)  {
        if (ptr[i] == b) {
        return;
    }
    }

}

int main() {
    int* data = nullptr;  // массив данных
    double* ans = nullptr;  // массив усредненных времен для каждого эксперимента
    int time1 = 0;
    for (int N = 100; N < 100000; N += 100) {
        ans = new double[1000];
        for (int repeats = 0; repeats < 100; ++repeats) { 
            auto begin = std::chrono::steady_clock::now();
            data = new int[N];
            randomize(data, N, 1001);
            finder(data, N);
            // HERE your code
            // Реализуйте заполнение массива случайными числами и поиск элемента в массиве
            // ...
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