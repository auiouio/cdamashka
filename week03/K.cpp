#include <iostream>

using namespace std;

#ifndef N
#define N 3
#endif

int trace(int (&arr)[N*N]){
    int tr = 0;
    for (int i = 0; i < N; i++){
        tr += arr[i+N*i];
    }
    return tr;
}

int main() { 
    int a[N*N] = {0};
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> a[j+i*N];
        }
    }
    cout << trace(a) << endl;
    return 0;
}