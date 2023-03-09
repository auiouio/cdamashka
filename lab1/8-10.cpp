#include <iostream> 
#include <chrono>
#include <random>

#ifndef N
#define N 150000
#endif

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void uporyadochenni_massiv(int (&array)[N]) {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned>dstr(0, N);

    for (int i = 0; i < N; i++) {
        array[i] = dstr(rng);
    }
}

int strA(int (&arr)[N], int search_for) {
    if (arr[0] == search_for) {
        return arr[0];
    }
    for (int i = 0; i < N; i++) {
        if (arr[i] == search_for) {
            swap(arr[0], arr[i]);
            return arr[0];
        }
    }
    return -1;
}

int strB(int (&arr)[N], int search_for) {
    if (arr[0] == search_for) {
        return arr[0];
    }
    for (int i = 0; i < N; i++) {
        if (arr[i] == search_for) {
            swap(arr[i], arr[i-1]);
        }
    }
    return -1;
}

int strC(int (&arr)[N], int search_for, int (&counter)[N]) {
    if (arr[0] == search_for) {
        counter[0]++;
        return arr[0];
    }
    for (int i = 0; i < N; i++) {
        if (arr[i] == search_for) {
            counter[i]++;
            if (counter[i] >counter[i-1]) {
                swap(counter[i], counter[i-1]);
                swap(arr[i], arr[i-1]);
                swap(arr[i], arr[i-1]);
                return arr[i-1];
            } else {
                return arr[i];
            }
        }
    }
    return -1;
}

int main ( ) {
    int arr[N] = {0};
    int search_for = 0;
    int counter[N] = {0};
    uporyadochenni_massiv(arr);
    auto begin = std::chrono::steady_clock::now();
    /* //равномерно
    for (int i = N; i > 0; i--) {
        search_for = i - 10; 
        //strA(arr, search_for);
        //strB(arr, search_for);
        strC(arr, search_for, counter);
    } */
     //NEravnomerno
     for (int i = N; i > 0; i--) {
         if (i <= N/2) {
             search_for = N/2;
         } else {
             search_for = i - 10;
         } 
         //strA(arr, search_for);
         //strB(arr, search_for);
         strC(arr, search_for, counter);
     }
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << time_span.count() << std::endl;
    
    return 0;
}
