#include <iostream>

using namespace std;

int recursive_power(int base, int power) {
    int res = 1;
    int i = 0;
    while (i < power) {
        res *= base;
        i ++;
    }
    return res;
}

int main() {
    int base = 0; int power = 0;
    cin >> base >> power;
    cout << recursive_power(base, power) << endl;
    return 0;
}