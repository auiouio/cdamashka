#include <iostream>

using namespace std;

#ifndef N
#define N 10  // actual size of the array
#endif

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

int partishn(int (&array)[N], int ind_left_base, int ind_right_base){
    int pivot = array[ind_right_base];
    int l = ind_left_base;
    for (int i = ind_left_base; i <= ind_right_base; i++) {
        if (array[i] < pivot){
            swap(array[i], array[l]);
            l++;
        }
    }
    swap(array[l], array[ind_right_base]);
    return l;
}

void qsort(int (&array)[N], int ind_left_base, int ind_right_base){
    if(ind_left_base >= ind_right_base){ 
        return;
    }
    int pivot = partishn(array, ind_left_base, ind_right_base);
    qsort(array, ind_left_base, pivot - 1);
    qsort(array, pivot + 1, ind_right_base);
}

int main() {
    int a[N] = {0};
    for (int i = 0; i<N; i++){
        a[i] = rand();
    } 
    for (int i = 0; i<N; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    qsort(a, 0, N-1);
    for (int i = 0; i<N; i++){
        cout << a[i] << ' ';
    }
    return 0;
}