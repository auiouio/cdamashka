#include <iostream>
#include <cmath>

using namespace std;

long int fibSquareRecursive(int n, long int* fib) {
    if (n == 0 or n == 1) {
        return 1;
    }
    if (n == 2) {
        return 4;
    }
    else {
         if (fib[n - 1] == -1) {
            fib[n - 1] = fibSquareRecursive(n - 1, fib);
        }
        if (fib[n - 2] == -1) {
            fib[n - 2] = fibSquareRecursive(n - 2, fib);
        }
        if (fib[n - 3] == -1) {
            fib[n - 3] = fibSquareRecursive(n - 3, fib);
        }
        return (2 * fib[n - 1] + 2 * fib[n - 2] - fib[n - 3]);
    }
}

int main()
{
    int n = 0;
    cin >> n;

    long int* fib = new long int[n+1];
    for (int i = 0; i < n; i++) {
        fib[i] = -1;
    }

    double fibn_squared = fibSquareRecursive(n, fib);

    cout << fibn_squared << endl;

    delete[] fib;

    return 0;
}







