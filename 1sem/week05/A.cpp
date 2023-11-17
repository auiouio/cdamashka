#include <iostream>

using namespace std;

int main() {
    double nol = 0.;
    double* ptr = &nol;
    cout << ptr << ' ' << *ptr << endl;
    cout << ptr-3 << ' ' << *(ptr-3) << endl;
    cout << ptr+5 << ' ' << *(ptr+5) << endl;
    return 0;
}