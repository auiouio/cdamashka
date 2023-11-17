#include <iostream>
#include <random> 
#include <fstream>
#include <chrono>

using namespace std;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

void shell_sort(int arr[], size_t N) {
    for (int d = N/2; d > 0; d /= 2) {
        for (int i = 1; i <= N-d; i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    }
}

int max_i (size_t N) {
    int i = 0;
    while (pow(2, i) - 1 <= N) {
        i++;
    }
    return i;
}

int fib(int a) {
    int res = 0;
    if (a == 0) {
        res = 0;
    } else if (a == 1) {
        res = 1;
    } else {
        res = fib(a-1) + fib(a-2);
    }
}

int max_i_fib(size_t N) {
    int max = 0;
    int i = 0;
    while (max < N) {
        max = fib(i);
        i++;
    }
    if (max > N) {
        max = fib(i-1);
    } else {
        max = fib(i);
    }
    return fib(i-2);
}

int ind_fib(size_t N) {
    int max = 0;
    int i = 0;
    while (max < N) {
        max = fib(i);
        i++;
    }
    if (max > N) {
        return i-1;
    } else {
        return i;
    }
}

void hibbard_sort(int arr[], size_t N) {
    int i = max_i(N);
    for (int d = i; d > 0; d--) {
        for (int i = 1; i <= N-d; i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    }

}

void fib_sort (int arr[], size_t N) {
    for (int i = 1; i <= N-max_i_fib(N); i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    for (int j = ind_fib(N)-1; j>0; j--) {
        for (int i = 1; i <= N-fib(j); i++) {
            for (int j = i; j>0 and arr[j-1] > arr[j]; j--) {
                swap(arr[j], arr[j-1]);
            }
        }
    }
}

void create_outfile(int arr[], int brr[]) {
    std::ofstream out("shsort3.csv", std::ios::out);
    for (int i = 0; i < brr[i]; ++i) {
        if (out.is_open()) {
            out << arr[i] << "," << brr[i] << endl;
        }
    }
    out.close();
}

void randomize(int arr[], size_t N, int seed) {
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, N);
    for (int i = 0; i < N; i++) {
        arr[i] = dstr(rng);
        i++;
    }
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
        shell_sort(arr, N);
        //hibbard_sort(arr, N);
        //fib_sort(arr, N);
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        time1 += time_span.count();
        //nSwaps[i] = combSort(arr, N);
        times[i] = time1;
    }
    create_outfile(times, Ns);
    
    return 0;
}