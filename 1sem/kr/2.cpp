#include <iostream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    int a[100];
    a[0] = 0;
    for (int i = 1; i < 100; ++i) {
        if (i % 10 != 0) {
            a[i] = a[i-1] + 19 - (i/10)*2;
        } else {
            a[i] = a[i-1] + 21 - (i/10)*2;
        }
    }
    cout << a[n];
}























