#include <iostream>
#include <algorithm> 

using std::endl;
using std::cout;
using std::cin;

#ifndef N
#define N 9
#endif

int main() {
    int array[N];
    for (int i = 0; i < N; ++i) {
        cin >> array[i]; 
    }

    std::sort(array, array + N);

    int lonely_num = array[0];
    for (int i = 1; i < N; ++i) {
        if ((array[i] != array[i-1]) and (array[i] != array[i+1])) {
            lonely_num = array[i];
        } 
    }
    cout << lonely_num << '\n';
    return 0;
}