#include <iostream>

using namespace std;

int main() {
    int N = 0;
    int counter = 0;
    cin >> N;
    int a[6] = {1, 7, 28, 49, 63, 98};
    for (int i = 5; i>=0; i--) {
        while (N - a[i] > 0 and N != 0){
            counter++;
            N = N - a[i];
        }
    }
    cout << counter + N;
    return 0;
}