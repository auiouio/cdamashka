#include <iostream>

using namespace std;

struct Time
{
    int h;
    int min;
    int sec;
};

int main() {
    Time arr[2];
    cin >> (arr[0]).h >> (arr[0]).min >> (arr[0]).sec;
    cin >> (arr[1]).h >> (arr[1]).min >> (arr[1]).sec;
    int t[3] = {0};
    t[0] = (arr[0]).h + (arr[1]).h;
    t[1] = (arr[0]).min + (arr[1]).min;
    t[2] = (arr[0]).sec + (arr[1]).sec;
    if ((arr[0]).sec + (arr[1]).sec > 59) {
        t[1]++;
    }
    if ((arr[0]).min + (arr[1]).min > 59) {
        t[0]++;
        t[1] = t[1]%60;
    } 
    if ((arr[0]).sec + (arr[1]).sec > 59) {
        t[1]++;
    }  
    cout << t[0]%24 << ' ' << t[1]%60 << ' ' << t[2]%60 << endl;
}
