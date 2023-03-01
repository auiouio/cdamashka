#include <iostream>

using namespace std;

#ifndef N
#define N 5
#endif

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

int main() {
    int a[N] = {0};
    for (int i = 0; i<N; i++) {
        cin >> a[i]; 
    }
    
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N-i-1; j++) {
            if (a[j] < 0 and a[j+1] >= 0) {
                swap(a[j], a[j+1]);
            }
        }
    }

    for (int i = 0; i<N; ++i) {
        cout << a[i] << ' '; 
    }
    cout << endl;
    return 0;
}