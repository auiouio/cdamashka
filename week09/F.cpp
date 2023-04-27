#include <iostream>

using namespace std;

struct lesson {
    int begin;
    int end;
};

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
} 

int main() {
    int N = 0;
    cin >> N;
    lesson L[100];
    for (int i = 0; i < N; i++) {
        cin >> L[i].begin >> L[i].end;
    }
    int j = 0;
    while (j < N) {
        if (j == 0)
            j++;
        if (L[j].begin >= L[j - 1].begin)
            j++;
        else {
            swap(L[j].end, L[j - 1].end);
            swap(L[j].begin, L[j - 1].begin);
            j--;
        }
    } // отсортировали по возрастанию начала лекций
    int curBegin = 0, curEnd = 0; // будут считать время начала и окончания лекции на которой сидим
    int counter = 0;
    for (int i = 0; i < N; i++) {
        if (L[i].begin != curBegin and curEnd <= L[i].begin) {
            curBegin = L[i].begin;
            curEnd = L[i].end;
            counter++;
        }
    }
    cout << counter << endl;
    return 0;
}