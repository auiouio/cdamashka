#include <iostream>

using namespace std;

int count_ways(int x) {
    if (x == 0) {
        return 1;
    } else if (x == 1) {
        return 1;
    } else if (x == 2) {
        return 2;
    } else {
        int dp[3] = {1, 1, 2}; // dp[0]=1, dp[1]=1, dp[2]=2

        for (int i = 3; i <= x; i++) {
            int temp = dp[0] + dp[1] + dp[2];
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = temp;
        }

        return dp[2];
    }
}

int main() {
    int x;
    cin >> x;

    int ways = count_ways(x);

    cout << ways << endl;

    return 0;
}