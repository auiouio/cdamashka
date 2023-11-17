#include <iostream>

using namespace std;

int fibonacci(int i) {
    int res = 0;
    if (i == 0) {
        res = 1;
    } else if (i == 1) {
        res = 1;
    } else {
        res = fibonacci(i - 1) + fibonacci(i - 2);
    }
    return res;
}

int main() {
    int i = 0;
    cin >> i;
    cout << fibonacci(i) << endl;
    return 0;
}


int main() {

    return 0;
}