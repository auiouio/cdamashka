#include <iostream>
#include <cmath>

using namespace std;

void plain(int n) {
    if (n % 2 == 0) {
        cout << "NO" << endl;
        return;
    } else {
        for (int i = 3; i < sqrt(n); i += 2) {
            if (n % i == 0) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
}

int main() {
    int n = 0;
    cin >> n; 
    plain(n);
    return 0;
}