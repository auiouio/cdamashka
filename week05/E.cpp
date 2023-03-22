#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool reserve_memory(size_t N, int *&dst);
void free_memory(int*);

bool reserve_memory(size_t N, int *&dst) {
    if (dst = nullptr) {
        int* dst = new int[10];
        return true;
    } else {
        return false;
    }
}

void free_memory(int* dst) {
    delete [] dst;
}

int main() {
    int N = 0;
    int* ptr = nullptr;
    cin >> N;
    cout << reserve_memory(N, ptr) << endl;
    free_memory(ptr);
    return 0;
}