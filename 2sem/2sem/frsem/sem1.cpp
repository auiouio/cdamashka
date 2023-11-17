#include <iostream>

using namespace std;

struct IntAbstractQueue {
    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual bool is_empty() const = 0;
    virtual bool is_full() const = 0;

    virtual ~IntAbstractQueue() { }
};

struct IntStack: IntAbstractQueue {
    void push(int x) override {
        data[top++] = x;
    }
    int pop() override {
        return data[--top];
    }
    bool is_empty() const override {
        return 0 == top;
    }
    bool is_full() const override {
        return 10 == top;
    }
private:
    unsigned top = 0;
    int data[10];
};

struct IntStackWithMax: IntAbstractQueue {
    IntStack stack;
    void push(int x) override {
        stack.push(x);
    }

    int pop() override {
        return stack.pop();
    }

    bool is_empty() const override {
        return stack.is_empty();
    }

    bool is_full() const override {
        return stack.is_full();
    }

    int get_max() const {
        int max = INT_MIN;
        IntStack temp_stack = stack; // Create a temporary stack to avoid modifying the original stack.
        while (!temp_stack.is_empty()) {
            int value = temp_stack.pop();
            if (value > max) {
                max = value;
            }
        }
        return max;
    }
};


#include <cassert>
void with_queue_do(IntAbstractQueue &q) {
    assert(q.is_empty());
    q.push(1);
    assert(!q.is_empty());
    assert(1 == q.pop());
    assert(q.is_empty());
    for (int cnt = 0; cnt != 10; ++cnt)
        q.push(cnt);
    assert(q.is_full());
}
void with_stack_do(IntStack &s) {
    with_queue_do(s); 
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == s.pop());
    assert(s.is_empty());
}
void with_stackwithmax_do(IntStackWithMax &swm) {
    with_queue_do(swm);
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == swm.get_max() and cnt - 1 == swm.pop());
    assert(swm.is_empty()); 
}

int main() {
    IntStackWithMax swm;
    with_stack_do(swm);
    with_stackwithmax_do(swm);
    return 0;
}