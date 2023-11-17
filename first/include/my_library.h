#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

template <typename T>
struct Comparator {
    virtual bool operator()(T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int> {
    bool operator()(int const& lha, int const& rha) const override {
        return lha < rha;
    }
};

#endif