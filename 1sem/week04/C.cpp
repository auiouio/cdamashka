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

void kucha_sort(int (&arr)[N], int i, int max_len){
    int max = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if ((left < max_len) and (arr[max] < arr[left])){
        max = left;
    }
    if ((right < max_len) and (arr[max] < arr[right])){
        max = right;
    }
    if (max!=i){
        swap(arr[max], arr[i]);
        kucha_sort(arr, max, max_len);
    }
    
}

void cheops_sort(int (&arr)[N]){
    for (int i = N/2; i>=0; i--){
        kucha_sort(arr, i, N);
    }
    
    for (int i = N-1; i>=0; i--){
        swap(arr[0], arr[i]);
        kucha_sort(arr, 0, i);
    }
}

int main(){
    int a[N] = {0};
    for (int i = 0; i < N; i++){
        a[i] = rand() % N*10;
    }
    for (int i = 0; i < N; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    cheops_sort(a);
    for (int i = 0; i < N; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    return 0;
}