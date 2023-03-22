#include <cstring>

char *resize(const char *buf, size_t size, size_t new_size) {
    char *ptr = new char[new_size];
    memcpy(ptr, buf, size);
    delete [] buf;
    return ptr;
}

int main() {
    char *a = new char[10];
    char *b = resize(a, 10, 11);
    delete[] b;
}