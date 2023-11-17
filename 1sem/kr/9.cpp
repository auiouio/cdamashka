#include <iostream>

using namespace std;

struct interval {
    int begin;
    int end;
};

int main() {
    interval I[10];
    int N = 0, time = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> I[i].begin >> I[i].end; 
    }
    for (int i = 0; i < N; i++) {
        if (I[i].end > I[i+1].begin) {
            time += I[i].end - I[i+1].begin;
            int temp = I[i+1].begin;
            I[i].end = temp;
            I[i+1].begin = I[i].end;
    }
    }
    for (int i = 0; i < N; i++) {
        time += I[i].end - I[i].begin;
        
    }
    cout << time + 1 << endl;
    return 0;
}