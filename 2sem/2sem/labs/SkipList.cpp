#include <iostream>
#include <cstdlib> 

template <typename T>
class SkipList {
    private:
    struct Node {
        int key;
        T value;
        Node** next; // Указатель на массив указателей на следующие узлы

        Node(int k, T val, int level) : key(k), value(val) {
            next = new Node*[level + 1];
            for (int i = 0; i <= level; ++i) {
                next[i] = nullptr;
            }
        }

        ~Node() {
            delete[] next;
        }
    };

    const float probability; // Вероятность добавления элемента на более высокий уровень
    const int maxLevels; // Максимальное количество уровней

    Node* head;

    int getRandomLevel() const {
        int level = 0;
        while (rand() / static_cast<float>(RAND_MAX) < probability && level < maxLevels) {
            level++;
        } // рандомное число преобразуем в число от 0 до 1, сравниваем с нашей вероятностью
        return level;
    }

    // функция для копирования узлов
    Node* copyNode(const Node* sourceNode, int levels) {
        if (sourceNode == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(sourceNode->key, sourceNode->value, levels);
        for (int i = 0; i <= levels; ++i) {
            newNode->next[i] = copyNode(sourceNode->next[i], levels - 1);
        }

        return newNode;
    }
    // Функция удаления узлов
    void clear() {
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next[0];  // Сохраняем следующий узел перед удалением текущего
            delete current;                 // Удаляем текущий узел
            current = next;                 // Переходим к следующему узлу
        }

        // После удаления всех узлов, устанавливаем head в nullptr
        head = nullptr;
    }


    public:
    // Конструктор по умолчанию
    SkipList(int maxLvl, float p): maxLevels(maxLvl), probability(p) {
        head = nullptr;
    };

    // Конструктор копирования
    SkipList(const SkipList& other) : probability(other.probability), maxLevels(other.maxLevels), head(nullptr) {
        head = copyNode(other.head, maxLevels - 1);
    }

    // Оператор копирующего присваивания
    SkipList& operator=(const SkipList& other) {
        if (this != &other) {
            // Освобождаем ресурсы текущего объекта
            clear();

            // Копируем узлы из другого объекта
            head = copyNode(other.head, maxLevels - 1);

            // Копируем остальные данные
            probability = other.probability;
            maxLevels = other.maxLevels;
        }
        return *this;
    }

    bool isEmpty() const {
        return head == nullptr;
    };

};