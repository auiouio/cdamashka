#include <iostream>
#include <chrono>

using namespace std;

#ifndef N
#define N 200000

#endif

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void sort(int (&array)[N]) {
    int help = N;
	while(help--) {
		bool swapped = false;
		
		for(int i = 0; i < N; i++)
		{
			if(array[i] > array[i + 1])
			{
				swap(array[i], array[i + 1]);
				swapped = true;
			}
		}
		
		if(swapped == false)
			break;
	}
}

int binsearch(int (&array)[N], int r){
    int i = 0;
    int start = 0;
    int final = N-1;
    
     while (start < final) {
        i = (start + final)/2;
        if (array[i] == r) {
            final = i;
        } else {
            start = i;
        }
        if (start == final - 1) {
            return start;
        }
    }
    return start - 1;
}



int main () {
    int a[N] = {0};
    int s = 0;
    int r = 0;
    r = rand();
    for (int i=0; i<N; i++){
        a[i] = rand();
    }
    for (int i = 0; i<30; i++){
        auto begin = std :: chrono :: steady_clock :: now ();
        for ( unsigned cnt = 100000; cnt != 0 ; --cnt )
            binsearch(a, r);
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