#include <algorithm> 
#include <iostream>

using namespace std;

int main() {
  int n;
  std::cin >> n;
  long long cost[n];
  for (int i = 0; i < n; ++i) {
    cin >> cost[i];
  }
  long long max_num, money;
  cin >> money >> max_num;
  sort(begin(cost), end(cost));
  int i = 0, ans = 0;
  while (i < n && money > 0) {
    int num = min(max_num, money / cost[i]);
    money -= num * cost[i];
    ans += num;
    ++i;
  }
  cout << ans;
}
