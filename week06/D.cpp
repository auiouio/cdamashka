#include <iostream>

using namespace std;

void swap(int& lha, int& rha) {
    int tmp = lha;
    lha = rha;
    rha = tmp;
}

struct Streets
{
    int xbegin;
    int ybegin;
    int xend;
    int yend;
} street1, street2;

int main() {
    cin >> street1.xbegin >> street1.ybegin >> street1.xend >> street1.yend;
    cin >> street2.xbegin >> street2.ybegin >> street2.xend >> street2.yend;

    if (street1.xbegin > street1.xend) {
        swap(street1.xbegin, street1.xend);
    }
    if (street1.ybegin > street1.yend) {
        swap(street1.ybegin, street1.yend);
    }
    if (street2.xbegin > street2.xend) {
        swap(street1.xbegin, street1.xend);
    }
    if (street2.ybegin > street2.yend) {
        swap(street1.ybegin, street1.yend);
    }
    if (street1.xbegin <= street2.xend and street1.xend >= street2.xbegin and
        street1.ybegin <= street2.yend and street1.yend >= street2.ybegin) {
            cout << "NO" << endl;
        }
    else {
        cout << "YES" << endl;
    }

    return 0;
}