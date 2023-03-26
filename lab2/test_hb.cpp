#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;

int test(int* ptr, size_t N);

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

int test(int* ptr, size_t N) {
    for (int i = 0; i<N; i++) {
        if (ptr[i]>ptr[i+1]) {
            cout << "Тест не прошел" << endl;
            break; 
        }
    }
    cout << "Тест пройден" << endl;
    return 0;
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
    test(ptr, N);
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


int main() {
    int* data = nullptr;  // массив данных
    int time1 = 0;
    for (int repeats = 0; repeats < 10; ++repeats) {
        int N = 9;
        data = new int[N];
        randomize(data, N, 1001); 
        for (int i = 0; i < N; i++) {
            cout << data[i] << ' ';
        }
        cout << endl;
        cout << "aa" << endl;
        hb(data, N);        
        bubble_sort(data, N);
        for (int i = 0; i < N; i++) {
            cout << data[i] << ' ';
        }
        cout << endl;
        //delete[] data;
    }
    return 0;
}