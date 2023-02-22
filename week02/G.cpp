#include <iostream>

using namespace std;

void palindrom(int n) {
    int n_reverse = 0, m = n;
    while (m > 0) {
        n_reverse = 10 * n_reverse + m % 10;
        m /= 10;
    }
    
    if (n == n_reverse) {
        cout << "YES" <<  endl;
    } else {
        cout << "NO" << endl;
    }
    return;
}

int main() {
    int n = 0;
    cin >> n;
    is_palindrom(n);
    return 0;
}