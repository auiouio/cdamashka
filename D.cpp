#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int x = 0, y = 0, nod = 0;
    cin >> x >> y;
    while (x != y) {
    if (x>y) {
      x = x-y;
    }
    else {
      y = y-x;
    }
  }
  cout << x;
}