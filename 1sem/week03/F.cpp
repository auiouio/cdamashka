#include <iostream>

using namespace std;

#ifndef N
#define N 5
#endif

int binsearch(int (&array)[N]){
    int i = 0;
    int start = 0;
    int final = N-1;
    
     while (start < final) {
        i = (start + final)/2;
        if (array[i] == 1) {
            final = i;
        } else {
            start = i;
        }
        if (start == final - 1) {
            return start;
        }
    }
    return start - 1;
}

int main() { 
    int a[N] = {0};
    for (int i = 0; i < N; i++){
        cin >> a[i];
    }
    cout << binsearch(a) << endl;
    return 0;
}