#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a = 0, b = 0, c = 0, D = 0;
    float x_1 = 0, x_2 = 0;
    cin >> a >> b >> c;
    D = b*b - 4*a*c;
    x_1 = (-b + sqrt(D))/(2*a);
    x_2 = (-b - sqrt(D))/(2*a);
    if (a != 0) {
        if (D>0) {
            if (x_1 > x_2) {
            cout << x_2 << ' ' << x_1 << endl;
        }
            else if (x_1 < x_2) {
                cout << x_1 << ' ' << x_2 << endl;
            }
            }
            else if (D == 0) {
                cout << x_2 << endl;
            }
            else if (D < 0) {
                cout << '\n' << endl;
            }
    } else {
        cout << (-c/b) << endl;
    }
    return 0;
}