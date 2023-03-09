#include <iostream>
#include <chrono>
#include <random>

using namespace std;

#ifndef N
#define N 550000
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

void binsearch(int* a, int r){
    int left = 0;
    int right = N - 1;
    int mid = 0;
    while (left < right){
        mid = (left + right)/2;
        if (r == a[mid]){
            return;
        }
        if (r < a[mid]){
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
}



int main () {
    int a[N] = {0};
    int s = 0;
    int r = 0;
    for (int i=0; i<N; i++){
        a[i] = rand();
    }
    cout << endl;
    int random_index = 0;
    random_index = rand()%(N+1);
    r = a[random_index];
    cout << r << endl;
    for (int i = 0; i<100; i++){
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
    cout << s/100 << ' ' << s <<  endl;
    return 0;
}