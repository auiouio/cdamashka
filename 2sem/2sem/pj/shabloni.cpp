#include <iostream>

template<typename Type>
Type max(Type a, Type b) {
	return (a >= b ? a : b);
}


int main() {
    const int a = 1;
    const char bChar = 'b';
    //const int abMax = max<int>(a, bChar);
    const int abMax = max<int>(a, static_cast<int>(bChar));
    std::cout << abMax << std::endl;
    return 0;
}