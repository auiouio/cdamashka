#include <iostream>

using namespace std;

int main() {
    int k = 0, N = 0, S = 0;
    int count = 0;
    cin >> N >> k >> S;
    int a[S] = {0};
    int h = 0;   //будет считать проеханное
    for (int i = 0; i < S; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < S-1; i++) {
        if (a[i+1] - a[i] > k) {
            count = -1;
        }
    }
    if (count != -1) {
        for (int i = 0; i < S-1; i++) {
            if (a[i + 1] - h > k) {
                    h = a[i];
                    count++;
                }
        }
        count ++;
    }
    cout << count << endl;
    return 0;
}