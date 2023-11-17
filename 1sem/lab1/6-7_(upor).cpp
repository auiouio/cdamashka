#include <iostream> 
#include <chrono>
#include <random>

#ifndef N
#define N 500000
#endif

void create_array_1(int (&array)[N]) {
    for (int i = 0; i < N; i++){
        array[i] = i;
    }
}


int bin_search (int (&arr)[N], int left, int right, int search_for) {
    int center = (left + right) / 2.;
    if (arr[left] + arr[left + 1] == search_for && arr[left] != arr[left + 1]) {
        return arr[left], arr[left + 1];
    } else if (arr[right] + arr[right - 1] == search_for && arr[right] != arr[right - 1]) {
        return arr[right], arr[right - 1];
    } else if (arr[left + 1] == arr[right]){
        return -1;
    } else if (arr[right] + arr[right - 1] < search_for) {
        return -1;
    }else if (arr[left] + arr[left +1] > search_for) {
        return -1;
    } else if (2 * arr[center] < search_for) {
        return bin_search(arr, center, right, search_for);
    } else if (2 * arr[center] > search_for) {
        return  bin_search(arr, left, center, search_for);
    }
}

int main ( ) {
    int arr[N] = {0};
    int search_for = N-10;
    for (int i = 0; i < N; i++){
        arr[i] = i;
    }
    
    auto begin = std::chrono::steady_clock::now();
    for (int i = 500; i > 0; i--) {
        bin_search(arr, 0, N-1,search_for);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << time_span.count() << std::endl;
    
    return 0;
}