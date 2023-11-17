#include <iostream>

using namespace std;

#ifndef N
#define N 2
#endif

#ifndef M
#define M 4
#endif


void sort2d(int (&array)[N][M]) {
    int a[N*M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[j+M*i] = array[i][j];
        }
    }
    
    for (int i = 0; i<N*M; ++i) {
        cout << a[i] << ' ';
    }
    cout << '\n';

    for (int j = 0; j < N*M; j++) {
        int num = a[j];
        int k = j - 1;
        while (k >= 0 and num < a[k]) {
            a[k + 1] = a[k];
            k--; 
            a[k + 1] = num;
        }
        }

    for (int i = 0; i<N*M; ++i) {
    cout << a[i] << ' ';
    }
    cout << '\n';

    for (int i = 0; i<N*M; i++) {
        array[i/M][i%M] = a[i];
    }
    return; 
}

int main() {
    int array[N][M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> array[i][j]; 
        }
    }   
    sort2d(array);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << array[i][j] << ' '; 
        }
        cout << '\n';
    }  
    return 0;
}
