#include <iostream>

using namespace std;

int toNorm(string num) {
    int dec = 0;
    int power = 1; 
    for (int i = num.length() - 1; i >= 0; i--) {
        int digit = num[i] - '0'; 
        dec += digit * power;
        power *= 7; 
    }
    return dec;
}

int main() {
    int N = 0;
    cin >> N;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        string num;
        cin >> num;
        sum += toNorm(num); 
    }
    string chetire = "";
    do {
        int remainder = sum % 4;
        chetire = to_string(remainder) + chetire;
        sum /= 4;
    } while (sum != 0);

    cout << chetire << endl;
    return 0;
}