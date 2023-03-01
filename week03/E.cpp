#include <iostream>

using namespace std;

#ifndef N
#define N 3
#endif

int main() {
    int a[N] = {0};
    int b[N] = {0};
    int M = 2*N;
    int c[M];
    for (int i = 0; i<N; i++) {
        cin >> a[i]; 
    }
    for (int i = 0; i<N; ++i) {
        cin >> b[i]; 
    }
    int j = 0, k = 0, i = 0;
    while(j<N and k<N and i<M) {
        if (a[j] < b[k]) {
            c[i] = a[j];
            j++;
            i++;
        } else {
            c[i] = b[k];
            k++;
            i++;
        }
    }
    while (j<N) {
        c[k+j] = a[j];
        j++;
    }
    while (k<N) {
        c[k+j] = b[k];
        k++;
    }

    for (int i = 0; i<M; i++) {
        cout << c[i] << ' '; 
    }
    cout << endl;
    return 0;
}