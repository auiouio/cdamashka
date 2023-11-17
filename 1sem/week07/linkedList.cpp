#include <iostream>

// TODO: место для реализации вашей структуры Node
// и функции void push_front(Node*& head_ref, int new_data)

using std::cout;
using std::endl;

struct Node {
    int key = 0;
    Node *next = nullptr;
}; 

void push_front(Node*& head_ref, int new_key) {
    if (head_ref == nullptr) {
        head_ref = new Node;
        head_ref->key = new_key;
        return;
    }
    Node *new_node = new Node;
    new_node->key  = new_key;
    new_node->next = head_ref;
    head_ref = new_node;
    return;
}

void push_back(Node*& head_ref, int new_data)  {
    if (head_ref == nullptr) {
        head_ref = new Node;
        head_ref->key = new_data;
        return;
    }
    Node* current = head_ref;
    while (current->next != nullptr){
        current = current->next;
    }
    current->next = new Node;
    current->next->key = new_data;
}

void insert_after(Node*& prev_ref, int new_key) {
    if (prev_ref == nullptr) {
        return;
    }
    Node *current = prev_ref->next;
    prev_ref->next = new Node;
    prev_ref->next->key = new_key;
    prev_ref->next->next = current;
    return;
}

void destroy_list(Node*& head_ref) {
  if (head_ref == nullptr) {
        return;
    }
    while (head_ref->next != nullptr) {
        Node *current = head_ref->next->next;
        delete head_ref->next;
        head_ref->next = current;
    }
    delete head_ref->next;
    head_ref = nullptr;
}

void print_list(Node *head_ref) {
    if (head_ref == nullptr) {
        cout << endl;
        return;
    }
    cout << head_ref->key;
    Node *current = head_ref;
    while (current->next != nullptr) {
        cout << " " << current->next->key;
        current = current->next;
    }
    cout << endl;
}

Node* find(Node *head_ref, int key){
    Node* current = head_ref;
    while (current != nullptr){
        if (current->key == key) break;
        current = current->next;
    }
    return current;
    }

void remove_key(Node *&head_ref, int key){
    if (head_ref == nullptr) return;
    if (head_ref->key == key) {
        Node* new_head = head_ref->next;
        delete head_ref;
        head_ref = new_head;
        return;
    }
    Node* current = head_ref;
    while (current->next != nullptr){
        if (current->next->key == key){
            Node* new_node = current->next->next;
            delete current->next;
            current->next = new_node;
            return;
        }
        current = current->next;
    }
}
