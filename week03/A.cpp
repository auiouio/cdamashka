#include <iostream>

#ifndef N
#define N 1  // actual size of the array
#endif

using namespace std;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

int main() {
    int a[N] = {0};
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N/2; i++) {
        swap(a[i], a[N - 1 - i]);
    }
    for (int i = 0; i < N; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
    return 0;
}