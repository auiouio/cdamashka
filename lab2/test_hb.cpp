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

void hb(int a[], int N) {
    for (int i = 0; i < N; i ++) {
        if (a[i] > a[i+N/4]) {
            swap(a[i], a[i+1]);
        }
    }
}

void bubble_sort(int a[], size_t N) {
    int i = 0;
    while (i < N) {
        if (i == 0)
            i++;
        if (a[i] >= a[i - 1])
            i++;
        else {
            swap(a[i], a[i - 1]);
            i--;
        }
    }
    return;
}

void randomize(int a[], size_t N, int seed) {
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, N);
    for (int i = 0; i < N; i++)
    {
        a[i] = dstr(rng);
        i++;
    }
}

void create_outfile(double a[], size_t N, int step) {
    std::ofstream out("linsearch_extratime.csv", std::ios::out);
    for (int i = 0; i < N; ++i) {
        if (out.is_open()) {
            out << step * (i + 1) << "," << a[i] << endl;
        }
    }
    out.close();
}

int main() {
    int data[] = {0};
    double ans[100] = {0};
    int time1 = 0;
    for (int N = 100; N < 100000; N += 100) {
        for (int repeats = 0; repeats < 100; ++repeats) {
            ans[100] = {0};
            randomize(data, N, 1001); 
            hb(data, N);
            auto begin = std::chrono::steady_clock::now();
            bubble_sort(data, N);
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
            time1 += time_span.count();
        }
        ans[N/100 - 1] = time1;
    }
    create_outfile(ans, 999, 100);
    return 0;
}