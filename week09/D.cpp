#include <iostream>

using namespace std;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}


int main() {
    long int S = 0;
    int N = 0;
    cin >> S >> N;
    int a[N] = {0};
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    int j = 0;
    while (j < N) {
        if (j == 0)
            j++;
        if (a[j] >= a[j - 1])
            j++;
        else {
            swap(a[j], a[j - 1]);
            j--;
        }
    }
    int Sum = 0;
    int count = 0;
    for (int c = 0; c < N; c++) {
        if (Sum + a[c] <= S) {
            Sum = Sum + a[c];
            count++;
        } else {
            break;
        }    
    }
    cout << count;
    return 0;
}