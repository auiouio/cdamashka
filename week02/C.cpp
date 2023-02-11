#include <iostream>

using namespace std;

int main() {
    int n = 0;
    int power = 1;
    int res = 1;
    cin >> n;
    while (res < n) {
        res *= 2;
    } if (res == n) {
        cout << "YES" << endl;
    } else cout << "NO" << endl;
    return 0;
}