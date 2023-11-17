#include <iostream>

using namespace std;

int recursive_power(int base, int power) {
    int res = 1;
    int i = 0;
    if (power == 0) {
        res = 1;
    } else {
        res = base * recursive_power(base, power - 1);
    }
    return res;
}

int main() {
    int base = 0; int power = 0;
    cin >> base >> power;
    cout << recursive_power(base, power) << endl;
    return 0;
}