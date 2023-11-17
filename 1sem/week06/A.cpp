#include <iostream>

using namespace std;

struct Students {
    string name;
    int avgrade;
} Student;
 
int main() {
    int M = 0;
    Students arr[10];
    for (int i = 0; i < 10; i++) {
        cin >> (arr[i]).name >> (arr[i]).avgrade;
    }
    cin >> M;
    for (int i = 0; i < 10; i++) {
        if ((arr[i]).avgrade > M) {
            cout << (arr[i].name) << ' ';
        }
    }
    cout << endl;
    return 0;
}