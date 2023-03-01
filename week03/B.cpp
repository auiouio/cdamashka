#include <iostream>

using namespace std;

#ifndef N
#define N 10
#endif

int main() {
    int a[N] = {0};
    int b[N] = {0};
    for (int i = 0; i < N; i++){
        cin >> a[i];
        b[((i+1) % N)] = a[i];
    }
    for (int i = 0; i < N; i++){
        cout << b[i] << ' ';
    }
    cout << endl;
    return 0;
}