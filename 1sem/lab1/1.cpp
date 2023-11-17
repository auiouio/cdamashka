#include <iostream>
#include <chrono>

using namespace std;

#ifndef N
#define N 300000

#endif

void finder(int (&array)[N]) {
    int b = 11;
    int i = 0;
    while ((array[i] != b) and (i<N)) {
        i++;
    }
}

int main ( ) {
    int a[N] = {0};
    int s = 0;
    for (int i=0; i<N; i++){
        a[i] = rand() % 10;
    }
    for (int i = 0; i<30; i++){
        auto begin = std :: chrono :: steady_clock :: now ();
        for ( unsigned cnt = 100000; cnt != 0 ; --cnt )
            finder(a);
        auto end = std :: chrono :: steady_clock :: now ();
        auto time_span =
        std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end - begin) ;
        std :: cout << "\n\n" ;
        std :: cout << time_span.count () << std :: endl;
        s += time_span.count ();
    }
    cout << s/30 << ' ' << s <<  endl;
    return 0;
}