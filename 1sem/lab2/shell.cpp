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

void shell_sort(int arr[], size_t N) {
    for (int d = N/2; d > 0; d /= 2) {
        for (int i = 1; i <= N-d; i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    }
}

int max_i (size_t N) {
    int i = 0;
    while (pow(2, i) - 1 <= N) {
        i++;
    }
    return i;
}

int fib(int a) {
    int res = 0;
    if (a == 0) {
        res = 0;
    } else if (a == 1) {
        res = 1;
    } else {
        res = fib(a-1) + fib(a-2);
    }
}

int max_i_fib(size_t N) {
    int max = 0;
    int i = 0;
    while (max < N) {
        max = fib(i);
        i++;
    }
    if (max > N) {
        max = fib(i-1);
    } else {
        max = fib(i);
    }
    return fib(i-2);
}

int ind_fib(size_t N) {
    int max = 0;
    int i = 0;
    while (max < N) {
        max = fib(i);
        i++;
    }
    if (max > N) {
        return i-1;
    } else {
        return i;
    }
}

void hibbard_sort(int arr[], size_t N) {
    int i = max_i(N);
    for (int d = i; d > 0; d--) {
        for (int i = 1; i <= N-d; i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    }

}

void fib_sort (int arr[], size_t N) {
    for (int i = 1; i <= N-max_i_fib(N); i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    for (int j = ind_fib(N)-1; j>0; j--) {
        for (int i = 1; i <= N-fib(j); i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    }
}

void randomize(int arr[], size_t N, int seed) {
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, N);
    for (int i = 0; i < N; i++) {
        arr[i] = dstr(rng);
        i++;
    }
}

int main() {
    int time1 = 0;
    for (int repeats = 0; repeats < 10; ++repeats) {
        int N = 9;
        int arr[N] = {0};
        randomize(arr, N, 1230); 
        for (int i = 0; i < N; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
        cout << "aa" << endl;
        cout << N << ' ' << max_i_fib(N) << endl;
        //shell_sort(arr, N);
        //hibbard_sort(arr, N);
        fib_sort(arr, N);
        for (int i = 0; i < N; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
        //delete[] data;
    }
    return 0;
}