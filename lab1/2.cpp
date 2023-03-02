#include <iostream> 
#include <chrono>
#include <random>

#ifndef N
#define N 500000
#endif

//uporyadochenni massiv
void create_array_1(int (&array)[N]) {
    for (int i = 0; i < N; i++){
        array[i] = i;
    }
}

//NEuporyadochenni massiv
void create_array_2(int (&array)[N]) {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned>dstr(0, N);

    for (int i = 0; i < N; i++) {
        array[i] = dstr(rng);
    }
}

int search (int (&arr)[N], int search_for) {
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if (arr[i] + arr[j] == search_for && arr[i] != arr[j]) {
                return arr[i], arr[j];
            }
        }
    }
    return -1;
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
    create_array_2(arr);
    //create_array_1(arr);
    
    auto begin = std::chrono::steady_clock::now();
    for (int i = 500; i > 0; i--) {
        search(arr, search_for);
        //bin_search(arr, 0, N-1,search_for);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << time_span.count() << std::endl;
    
    return 0;
}