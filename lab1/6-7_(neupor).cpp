#include <iostream> 
#include <chrono>
#include <random>

using namespace std;

#ifndef N
#define N 300000
#endif

int search_perebor (int (&arr)[N], int search_for) {
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if (arr[i] + arr[j] == search_for && arr[i] != arr[j]) {
                return arr[i], arr[j];
            }
        }
    }
    return -1;
}


int main ( ) {
    int s = 0;
    int a[N] = {0};
    int search_for = N-10;
    for (int i=0; i<N; i++){
        a[i] = rand()%N;
    }
    for (int i = 0; i<30; i++){
        auto begin = std::chrono::steady_clock::now();
        search_perebor(a, search_for);
        auto end = std::chrono::steady_clock::now();
        auto time_span =
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << time_span.count() << std::endl;
        s+=time_span.count();
    }
    std::cout << s << ' ' << s/30 << endl;
    
    
    return 0;
}