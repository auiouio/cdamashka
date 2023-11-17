struct Node {
    int key;
    int value;
    Node* next;
};

struct Stack {
    Node* top = nullptr;       // указатель на вершину стека
};