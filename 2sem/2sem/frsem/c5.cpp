#include <iostream>
#include <cassert>

using namespace std;

struct SegmentAbstract {
    virtual int beg() const = 0;
    virtual int end() const = 0;

    virtual ~SegmentAbstract() { }
};

struct SegmentSimple final: SegmentAbstract {
    int beg() const override { return _beg; }
    int end() const override { return _end; }
    SegmentSimple(int beg, int end): _beg(beg), _end(end) { }
private:
    int const _beg, _end;
};

#include <algorithm>

struct SegmentSumm final : SegmentAbstract {
    int beg() const override {
        return std::min(segment1->beg(), segment2->beg());
    }

    int end() const override {
        return std::max(segment1->end(), segment2->end());
    }

    SegmentSumm() : segment1(nullptr), segment2(nullptr) { }

    SegmentSumm(const SegmentAbstract* s1, const SegmentAbstract* s2) : segment1(s1), segment2(s2) { }

private:
    const SegmentAbstract* segment1;
    const SegmentAbstract* segment2;
};

struct SegmentMultiply final : SegmentAbstract {
    int beg() const override {
        int max_beg = std::max(segment1->beg(), segment2->beg());
        int min_end = std::min(segment1->end(), segment2->end());
        if (max_beg > min_end) {
            return min_end; 
        }
        return max_beg;
    }

    int end() const override {
        int max_beg = std::max(segment1->beg(), segment2->beg());
        int min_end = std::min(segment1->end(), segment2->end());
        if (max_beg > min_end) {
            return max_beg; 
        }
        return min_end;
    }

    SegmentMultiply() : segment1(nullptr), segment2(nullptr) { }

    SegmentMultiply(const SegmentAbstract* s1, const SegmentAbstract* s2) : segment1(s1), segment2(s2) { }

private:
    const SegmentAbstract* segment1;
    const SegmentAbstract* segment2;
};

int main() {
    SegmentAbstract const *s1 = new SegmentSimple(1, 10);
    SegmentAbstract const *s2 = new SegmentSimple(5, 15);
    SegmentAbstract const *e  = new SegmentSimple(25, 20);

    SegmentAbstract const *summ_s1_s2 = new SegmentSumm(s1, s2);
    SegmentAbstract const *mult_s1_s2 = new SegmentMultiply(s1, s2);
    SegmentAbstract const *summ_s1_e = new SegmentSumm(s1, e);
    SegmentAbstract const *mult_s1_e = new SegmentMultiply(s1, e);
    
    assert(1 == summ_s1_s2->beg() and 15 == summ_s1_s2->end());
    assert(5 == mult_s1_s2->beg() and 10 == mult_s1_s2->end());
    assert(1 == summ_s1_e->beg() and 10 == summ_s1_e->end());
    assert(mult_s1_e->beg() > mult_s1_e->end());
    
    delete mult_s1_e;
    delete summ_s1_e;
    delete mult_s1_s2;
    delete summ_s1_s2;
    delete e;
    delete s2;
    delete s1;
    return 0;
}