#include <iostream>
 
using namespace std;

int main() {
    int x; // объявление переменной
    float y = 9.3, *ptr = nullptr; // инициализация
    ptr = &y;
    y = 17.2; // присвоение
    *ptr = 1.1;
    cout << y << ' ' << *ptr << endl;
}
// 2.3 8.3 9.3 17.2 23