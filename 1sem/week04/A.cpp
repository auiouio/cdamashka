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

void gnome_sort(int (&array)[N]) {
    int i = 0;
    while (i < N) {
        if (i == 0)
            i++;
        if (array[i] >= array[i - 1])
            i++;
        else {
            swap(array[i], array[i - 1]);
            i--;
        }
    }
    return;
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
    gnome_sort(a);
    for (int i = 0; i<N; i++){
        cout << a[i] << ' ';
    }
    return 0;
}