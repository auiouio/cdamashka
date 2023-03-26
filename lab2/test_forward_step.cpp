#include <iostream>
#include <random>

using namespace std;

#ifndef N
#define N 18  // actual size of the array
#endif

void swap(unsigned& lha, unsigned& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void forward_step(unsigned array[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned i = begin_idx; i < end_idx; i++) {
        if (array[i] > array[i + 1]) {
            swap(array[i], array[i + 1]);
        }
    }
    return;
}

void sort(unsigned array[], unsigned const begin_idx, unsigned const end_idx) {
    unsigned left = begin_idx, right = end_idx;
    while (left <= right) {
        forward_step(array, left, right);
        //backward_step(array, left, right);
        right--;
    }
}

void backward_step(unsigned arr[], unsigned const begin_inx, unsigned const end_inx) {
    unsigned i = end_inx;
    while (i > begin_inx) {
        if (arr[i] >= arr[i-1]) {
            i--;
        } else {
            swap(arr[i], arr[i-1]);
            i--;
        }
    }
    return;
}

void shaker_sort(unsigned array[], unsigned const begin_idx, unsigned const end_idx) {
    unsigned left = begin_idx, right = end_idx;
    while (left <= right) {
        forward_step(array, left, right);
        left++;
        backward_step(array, left, right);
        left++;
    }
}

int test(unsigned array[]) {
    sort(array, 0, N-1);
    for (int i = 1; i < N; i++) {
        if (array[i-1] > array[i]) {
            cout << "тест не прошел ";
            break; 
        }
    }
    return 0;
}

int main() {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, N-1);
    unsigned array[N] = {0};
    for (int i = 0; i < N; i++) {
        array[i] = dstr(rng);
        cout << array[i] << ' ';
    }
    cout << endl;

    test(array);
    //shaker_sort(array, 0, N-1);

    for (int i = 0; i < N-1; i++) {
        cout << array[i] << ' ';
    }
    cout << array[N-1] << endl;
    return 0;
}