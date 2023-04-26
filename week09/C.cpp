#include <iostream>

using namespace std;

int main() {
    int k = 0, M = 0, counter = 0;
    cin >> k;
    int a[k] = {0};
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    cin >> M;
    for (int i = k; i>0; i--) {
        while (M - a[i-1] >= 0 and M >= 0){
            counter++;
            M = M - a[i-1];
        }
    }
    cout << counter + M << endl;
    return 0;
}