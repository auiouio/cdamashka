#include <iostream>


using namespace std;

struct Cut {
    int length[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int price[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
};

int main() {
    int n;
    cin >> n;
    Cut cut;

    int dp[11] = {0}; // массив для хранения максимальной выручки для каждой длины

    for (int i = 1; i <= n; i++) {
        int max_price = 0;
        for (int j = 0; j < 10; j++) {
            if (cut.length[j] <= i) {
                max_price = max(max_price, cut.price[j] + dp[i - cut.length[j]]);
            }
        }
        dp[i] = max_price;
    }


    while (n > 0) {
        for (int i = 0; i < 10; i++) {
            if (cut.length[i] <= n && dp[n] == cut.price[i] + dp[n - cut.length[i]]) {
                cout << cut.length[i] << " ";
                n -= cut.length[i];
                break;
            }
        }
    }
    return 0;
}





