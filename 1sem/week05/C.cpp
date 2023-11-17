#include <iostream>

using namespace std;

int main() {
    int i = 0, h = 1;
    int* ptr = new int[20];
    while(h != 0) {
        cin >> h;
        ptr[i] = h;
        i++;
    }
    if (i == 1) {
        cout << 0 << endl;
    } else {
        for (int j = 0; j < i-2; j++) {
            cout << ptr[j] - ptr[j+1] << ' ';
        }
        cout << endl;
    }
    delete [] ptr;
    return 0;
}