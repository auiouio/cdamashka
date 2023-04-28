#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float N = 0., M = 0.;
    cin >> N >> M;
    int i = 2;
    if (int(N) % int(M) == 0) {
        cout << N/M << endl;
    } else {
        int num = 0;
        while (N != 0) {
            num = ceil(M/N);
            N = N*num - M;
            M = M*num;
            cout << num << ' ';
        }
    }
    cout << endl;
    return 0;
}