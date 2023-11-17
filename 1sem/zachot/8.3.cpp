#include <iostream>
 
using namespace std;

void Array1(int* arr, int size) { }; // по указателю, можем изменять массив
void Array2(int (&arr)[5]) { }; // по ссылке
void Array3(int arr[5]) { }; // по значению

int main() {
    int *ptr = new int[20];
    int arr[5] = {0}, arr2[25] = {0};
    Array2(arr);
    return 0;

}
