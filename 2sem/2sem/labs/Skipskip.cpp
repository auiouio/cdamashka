#include <iostream>
#include <cstdlib>
#include <iterator>
#include <set>
#include <vector>
#include <ctime>
#include <chrono>
#include <random>

template <typename T, typename Comparator = std::less<int>>
class SkipList {
private:
    Comparator comparator;
    size_t size;
    struct Node {
        int key;
        T value;
        Node** next; // Указатель на массив указателей на следующие узлы
        Node** prev; // Указатель на массив указателей на предыдущие узлы

        Node(int k, T val, int level) : key(k), value(val) {
            next = new Node*[level + 1];
            prev = new Node*[level + 1];
            for (int i = 0; i <= level; ++i) {
                next[i] = nullptr;
                prev[i] = nullptr;
            }
        }

        ~Node() {
            delete[] next;
            delete[] prev;
        }
    };

    float probability; // Вероятность добавления элемента на более высокий уровень
    int maxLevels;     // Максимальное количество уровней

    Node* head;
    std::multiset <T> elements;

    int getRandomLevel() const {
        int level = 0;
        while (rand() / static_cast<float>(RAND_MAX) < probability && level < maxLevels) {
            level++;
        }
        return level;
    }

    Node* copyNode(const Node* sourceNode, int levels) {
        if (sourceNode == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(sourceNode->key, sourceNode->value, levels);
        for (int i = 0; i <= levels; ++i) {
            newNode->next[i] = copyNode(sourceNode->next[i], levels - 1);
            newNode->prev[i] = nullptr; // Устанавливаем prev для скопированных узлов в начальное состояние
        }

        return newNode;
    }

    void clear() {
        while (head != nullptr) {
            Node* next = head->next[0];
            delete head;
            head = next;
        }
    }

public:
    SkipList(int maxLvl, float p) : size(0), maxLevels(maxLvl), probability(p) {
        head = nullptr;
    };

    template <typename I>
    SkipList(I first, I last, float p, int maxLvl) : size(0), probability(p), maxLevels(maxLvl), head(nullptr) {
        for (auto it = first; it != last; ++it) {
            insert(it->key, it->value);
        }
    }

    SkipList(const SkipList& other) : probability(other.probability), maxLevels(other.maxLevels), head(nullptr) {
        head = copyNode(other.head, maxLevels - 1);
    }

    SkipList& operator=(const SkipList& other) {
        if (this != &other) {
            clear();
            head = copyNode(other.head, maxLevels - 1);
            probability = other.probability;
            maxLevels = other.maxLevels;
        }
        return *this;
    }

    ~SkipList() {
        clear();
    }

    SkipList& operator=(SkipList&& other) noexcept {
        if (this != &other) {
            clear();
            size = other.size;
            probability = other.probability;
            maxLevels = other.maxLevels;
            head = other.head;
            other.size = 0;
            other.head = nullptr;
        }
        return *this;
    }

    bool isEmpty() const {
        return head == nullptr;
    };

    size_t getSize() const {
        return size;
    }

    void insert(const int& key, const T& value) {
        int levels = getRandomLevel();

        Node* newNode = new Node(key, value, levels);

        for (int i = levels - 1; i >= 0; --i) {
            Node* current = head;
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }

            if (current->next[i] != nullptr) {
                current->next[i]->prev[i] = newNode;
            }

            newNode->next[i] = current->next[i];
            newNode->prev[i] = current;
            current->next[i] = newNode;
        }

        if (newNode->next[0] != nullptr) {
            newNode->next[0]->prev[0] = newNode;
        }

        elements.insert(value);
        ++size;
    }

    template <typename I>
    void insert(I first, I end) {
        while (first != end) {
            insert(first->key, first->value);
            ++first;
        }
    }

    template <typename I>
    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        Iterator& operator++() {
            if (current) {
                current = current->next[0];
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            if (current && current->prev[0]) {
                current = current->prev[0];
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Node& operator*() const {
            return *current;
        };

    private:
        Node* current;
    };

    template <typename I>
    auto reverseIterator(I Iterator) {
        return std::make_reverse_iterator(Iterator);
    };

    template <typename I>
    I find(const T& value) const {
        Iterator<I> it;
        Node* current = head;

        for (int i = maxLevels - 1; i >= 0; --i) {
            while (current->next[i] != nullptr && comparator(current->next[i]->value, value)) {
                current = current->next[i];
            }

            if (current->next[i] != nullptr && current->next[i]->value == value) {
                return it(current->next[i]);
            }
        }

        return it(nullptr);
    }

    size_t count(const int& key) const {
        return elements.count(key);
    }

    template<typename I>
    I lower_bound(const int& key) const {
        Node* current = head;
        Node* lastNode = nullptr;

        for (int i = maxLevels - 1; i >= 0; --i) {
            while (current->next[i] != nullptr && comparator(current->next[i]->value, key)) {
                current = current->next[i];
            }

            if (current->next[i] != nullptr && current->next[i]->value == key) {
                lastNode = current->next[i];
            }
        }

        if (lastNode != nullptr && lastNode->value == key) {
            return Iterator<I>(lastNode);
        }

        if (lastNode == nullptr && current == head) {
            return Iterator<I>(head);
        }

        return Iterator<I>(current->next[0]);
    }

    template <typename I>
    I upper_bound(const int& key) const {
        Iterator<I> lower = lower_bound(key);

        if (lower != nullptr && lower->value == key) {
            ++lower;
        }

        return lower;
    }

    template <typename I>
    void erase(Iterator<I>& it) {
        if (it == nullptr) {
            return;
        }

        Node* nodeToRemove = it.current;

        for (int i = 0; i <= maxLevels - 1; ++i) {
            Node* current = head;
            while (current->next[i] != nullptr && current->next[i] != nodeToRemove) {
                current = current->next[i];
            }

            if (current->next[i] == nodeToRemove) {
                current->next[i] = nodeToRemove->next[i];
                if (nodeToRemove->next[i] != nullptr) {
                    nodeToRemove->next[i]->prev[i] = current;
                }
            }
        }

        delete nodeToRemove;
        it = Iterator<I>(nodeToRemove->next[0]);
        --size;
    }

    template <typename I>
    void erase(I first, I last) {
        while (first != last) {
            Node* nextNode = first.current->next[0];

            for (int i = 0; i <= maxLevels - 1; ++i) {
                Node* current = head;
                while (current->next[i] != nullptr && current->next[i] != first.current) {
                    current = current->next[i];
                }

                if (current->next[i] == first.current) {
                    current->next[i] = first.current->next[i];
                    if (first.current->next[i] != nullptr) {
                        first.current->next[i]->prev[i] = current;
                    }
                }
            }

            delete first.current;
            first.current = nextNode;
        }
    }

    template <typename I>
    std::pair<typename std::multiset<I>::iterator, typename std::multiset<T>::iterator> equal_range(const int& key) {
        return elements.equal_range(key);
    }
};

int main() {
    std::mt19937 rng(std::time(nullptr));
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    const int numTests = 1000;
    const int maxSize = 1000;

    for (int test = 0; test < numTests; ++test) {
        SkipList<int, std::less<int>> skipList(7, 0.5);

        for (int i = 1; i < 7; ++i) {
            int key = i;
            int value = i * 2;
            skipList.insert(key, value);
        }

        return 0;
    }
}

