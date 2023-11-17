#include <iostream>
#include <cmath>

using namespace std;

struct Cut {
    int length[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int price[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
};

int main() {
    int n = 0;
    cin >> n;

    Cut cuts;
    int dp[501];
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        for (int j = 0; j < 10; j++) {
            if (cuts.length[j] <= i and dp[i - cuts.length[j]] + cuts.price[j] > dp[i]) {
                dp[i] = dp[i - cuts.length[j]] + cuts.price[j];
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}