#include <iostream>
#include <random> 
#include <fstream>
#include <chrono>

using namespace std;

void randomize(int arr[], size_t N, unsigned seed) {
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(0, N);
    for (int i = 0; i < N; i++)
    {
        arr[i] = dstr(rng);
        i++;
    }
}

int iter_comb(int arr[], size_t N, int step) {
    int i = 0;
    int j = step;
    int swap;
    int swapCount = 0;
    
    while (j < N) {
        if (arr[i] > arr[j]) {
            swap = arr[i];
            arr[i] = arr[j];
            arr[j] = swap;
            swapCount++;
        }
        i++;
        j++;
    }
    
    return swapCount;
}

int combSort(int arr[], size_t N) {
    int totalSwaps = 0;
    int iterSwaps = 0;
    
    for (int step = N / 2; step > 0; step /= 2) {
        iterSwaps = iter_comb(arr, N, step);
        totalSwaps += iterSwaps;
    }

    while (iterSwaps > 0) {
        iterSwaps = iter_comb(arr, N, 1);
        totalSwaps += iterSwaps;
    }

    return totalSwaps;
}

void create_outfile(int arr[], int brr[], int srr[]) {
    std::ofstream out("sort.csv", std::ios::out);
    for (int i = 0; i < srr[i]; ++i) {
        if (out.is_open()) {
            out << srr[i] << "," << arr[i] << "," << brr[i] << endl;
        }
    }
    out.close();
}

int main() {
    int minN = 100;
    int maxN = 10000;
    int Nstep = 100;
    int nExperiments = (maxN - minN) / Nstep + 1;
    cout << "Number of experiments: " << nExperiments << endl;
    
    int Ns[nExperiments];
    int times[nExperiments];
    int nSwaps[nExperiments];
    

    for (int i = 0; i < nExperiments; i++) {
        int N = i * Nstep + minN;
        std::cout << "N: " << N << std::endl;
        int time1 = 0;
        Ns[i] = N;
        
        int arr[N];
        randomize(arr, N, 666+N);
        auto begin = std::chrono::steady_clock::now();
        combSort(arr, N);
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        time1 += time_span.count();
        nSwaps[i] = combSort(arr, N);
        times[i] = time1;
    }
    create_outfile(times, nSwaps, Ns);
    
    return 0;
}