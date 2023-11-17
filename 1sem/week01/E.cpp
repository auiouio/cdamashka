#include <iostream>
#include <cmath>

using namespace std;

int nod(int x, int y) {
    while (x != y) {
        if (x>y) {
        x = x-y;
        }
        else {
        y = y-x;
        }
    }
    return x;
}

int main () {
    int x = 0, y = 0, nok = 0;
    cin >> x >> y;
    nok = (x*y)/(nod(x, y));
    cout << nok << endl;
    return 0;
}

