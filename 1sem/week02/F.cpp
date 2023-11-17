#include <iostream>

using namespace std;

long recursive_factorial(int n) {
    long res = 0;
    if (n == 0) {
        res = 1;
    } else {
        res = n * recursive_factorial(n - 1);
    }
    return res;
}

int main() {
    int n = 0;
    cin >> n;
    cout << recursive_factorial(n) << endl;
}