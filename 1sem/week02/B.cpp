#include <iostream>

using namespace std;

int main() {
    int i = 0, count = 0;
    cin >> i;
    while (i != 0) {
        if (i % 2 == 0) {
            count ++;
        } cin >> i;
    }
    cout << count << endl;
    return 0;
}