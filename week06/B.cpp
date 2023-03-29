#include <iostream>

using namespace std;

struct Students {
    string name;
    int avgrade;
} Student;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void swap_string(string &lha, string &rha) {
    string tmp = lha;
    lha        = rha;
    rha        = tmp;
}
 
void gnome_sort(int (&array)[], string (&arr)[], int N) {
    int i = 0;
    while (i < N) {
        if (i == 0) {
            i++;
        }
        else if (array[i] >= array[i - 1]) {
            i++;
        } 
        else {
            swap(array[i], array[i - 1]);
            swap_string(arr[i], arr[i - 1]);
            i--;
        }
    }
    return;
}

int main() {
    int N = 0, M = 0;
    cin >> N;
    int counter = 0;
    Students arr[N];
    for (int i = 0; i < N; i++) {
        cin >> (arr[i]).name >> (arr[i]).avgrade;
    }
    cin >> M;
    int gr[N];
    string st[N];
    for (int i = 0; i < N; i++) {
        if ((arr[i]).avgrade >= M) {
            gr[N] = (arr[i]).avgrade;
            st[N] = (arr[i]).name;
            counter++;
        }
    }
    gnome_sort(gr, st, counter);
    for (int i = 0; i < counter; i++) {
        cout << st[i] << ' ';
    }
    cout << endl;
    return 0;
}