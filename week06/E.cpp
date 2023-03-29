#include <iostream>

using namespace std;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

struct keys
{
    int begin;
    int end;
};

int main() {
    int N = 0;
    cin >> N;
    keys arr[N];
    for (int i = 0; i < N; i++) {
        cin >> (arr[i]).begin >> (arr[i]).end;
    }
    if (N == 1) {
        cout << "YES" << endl;
    }
    bool flag = true;
    for (int i = 0; i < N-1; i++) {
        if (((arr[i+1]).begin <= (arr[i]).end) and ((arr[i]).begin <= (arr[i+1]).end)) {
            flag = true;
        } else {
            flag = false;
            cout << "NO" << endl;
            break;
        }
    }
    if ((flag == true) and (N != 1)) {
        cout << "YES" << endl;
    }
    return 0;
}