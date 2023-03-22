#include <iostream>

using namespace std;

void input_array(int* ptr, size_t N);
void reverse(int* ptr, size_t N);
void print(const int* ptr, size_t N);

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void input_array(int* ptr, size_t N) {
    for (int i = 0; i < N; ++i) {
        cin >> ptr[i];
    }
}

void reverse(int* ptr, size_t N) {
    for (int i = 0; i<N/2; ++i) {
        swap(ptr[i], ptr[N-1-i]);
    }
}

void print(const int* ptr, size_t N) {
    for (int i = 0; i < N; ++i) {
        cout << ptr[i] << " ";
    }
    cout << endl;
}






int main() {
    int N = 0;
    //int* ptr = nullptr;
    cin >> N;
    int* ptr = new int[N];
    input_array(ptr, N);
    print(ptr, N);
    reverse(ptr, N);
    print(ptr, N);
    delete [] ptr;
    return 0;
}