#include <iostream>
#include <cstdlib> 
#include <iterator>
#include <set>


template <typename T, typename Comparator = std::less<int>>
class SkipList {
    private:
    size_t size;
    struct Node {
        int key;
        T value;
        Node** next; // Указатель на массив указателей на следующие узлы
        Node** prev;

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

    float probability; // Вероятность добавления элемента на более высокий уровень
    int maxLevels; // Максимальное количество уровней

    Node* head;
    std::multiset<T> elements;


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

    template <typename I>
    SkipList(I first, I last, float p, int maxLvl) : probability(p), maxLevels(maxLvl), head(nullptr) {
        for (auto it = first; it != last; ++it) {
            insert(it->key, it->value);
        }
    }
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

    // Оператор перемещения
    SkipList& operator=(SkipList&& other) noexcept {
        if (this != &other) {
            // Освобождаем ресурсы текущего объекта
            clear();

            // Перемещаем ресурсы из other в текущий объект
            size = other.size;
            probability = other.probability;
            maxLevels = other.maxLevels;
            head = other.head;

            // Обнуляем ресурсы в other
            other.size = 0;
            other.head = nullptr;
        }
        return *this;
    }

    bool isEmpty() const {
        return head == nullptr;
    };

    // Метод для получения размера списка
    size_t getSize() const {
        return size;
    }

    // Метод для вставки элемента с амортизационной сложностью O(logN)
    void insert(const int& key, const T& value) {
        int levels = getRandomLevel();

        Node* newNode = new Node(key, value, levels);

        // Вставляем новый элемент на каждый уровень списка с пропусками
        for (int i = levels-1; i>=0; --i) {
            Node* current = head;
            while (current->next[i] != nullptr and current->next[i].key < key) {
                current = current->next[i];
            };
            // Вставляем новый узел на текущем уровне
            newNode->next[i] = current->next[i];
            current->next[i] = newNode;
        }
        elements.insert(value); 
    }

    // Метод для вставки диапазона итератора 
    template <typename I>
    void insert(I first, I end) {

        while (first != end) {
            insert(first->key, first->value);
            first++;
        }
    }

    // Определение итератора
    template <typename I>
    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}

        // Операторы сравнения
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        // Операторы инкремента и декремента
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
            // Для двунаправленного итератора, если у вас есть указатель на предыдущий узел, вы можете использовать его.
            // Это потребует дополнительной информации в вашем классе SkipList.
            // Здесь я предполагаю, что у вас есть указатель на предыдущий узел в классе Node.
            if (current && current->prev) {
                current = current->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // Оператор разыменования
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
        Iterator it;
        Node* current = head;

        for (int i = maxLevels - 1; i >= 0; --i) {
            while (current->next[i] != nullptr && compare(current->next[i]->value, value)) {
                current = current->next[i];
            }

            if (current->next[i] != nullptr && current->next[i]->value == value) {
                return it(current->next[i]);
            }
        }

        return it(nullptr);
    }


    // Метод для подсчета количества вхождений заданного ключа
    size_t count(const int& key) const {
        return elements.count(key);
    }

    template<typename I>
    I lower_bound(const int& key) const {
        Node* current = head;
        Node* lastNode = nullptr;

        // Идем по списку вниз
        for (int i = maxLevels - 1; i >= 0; --i) {
            while (current->next[i] != nullptr && Comparator(current->next[i]->value, key)) {
                current = current->next[i];
            }

            // Сохраняем последний узел на текущем уровне, который не превышает key
            if (current->next[i] != nullptr && current->next[i]->value == key) {
                lastNode = current->next[i];
            }
        }

        // Если найден узел с заданным ключом, возвращаем итератор на него
        if (lastNode != nullptr && lastNode->value == key) {
            return Iterator(lastNode);
        }

        if (lastNode == nullptr && current = head) {
            return Iterator(head);
        }

        // Возвращаем итератор на первый элемент не меньше заданного
        return Iterator(current->next[0]);
    }

    template <typename I>
    I upper_bound(const int& key) const {
        Iterator lower = lower_bound(key);

        // Если lower_bound вернул итератор на узел с ключом равным key,
        // увеличиваем итератор, чтобы получить upper_bound
        if (lower != nullptr && lower->value == key) {
            ++lower;
        }

        return lower;
    }

    template <typename I>
    void erase(Iterator<I>& it) {
        if (it == nullptr) {
            // Итератор указывает за конец списка, ничего не удаляем
            return;
        }

        Node* nodeToRemove = it.current;

        // Обновляем указатели на следующие узлы перед удалением текущего узла
        for (int i = 0; i <= maxLevels - 1; ++i) {
            Node* current = head;
            while (current->next[i] != nullptr && current->next[i] != nodeToRemove) {
                current = current->next[i];
            }

            if (current->next[i] == nodeToRemove) {
                current->next[i] = nodeToRemove->next[i];
            }
        }

        // Удаляем текущий узел
        delete nodeToRemove;

        // Обновляем итератор, чтобы он указывал на следующий узел после удаленного
        it = Iterator(nodeToRemove->next[0]);
    }

    template <typename I>
    void erase(I first, I last) {
        while (first != last) {
            // Сохраняем указатель на следующий узел перед удалением текущего
            Node* nextNode = first.current->next[0];

            // Обновляем указатели на следующие узлы перед удалением текущего узла
            for (int i = 0; i <= maxLevels - 1; ++i) {
                Node* current = head;
                while (current->next[i] != nullptr && current->next[i] != first.current) {
                    current = current->next[i];
                }

                if (current->next[i] == first.current) {
                    current->next[i] = first.current->next[i];
                }
            }

            // Удаляем текущий узел
            delete first.current;

            // Переходим к следующему узлу
            first.current = nextNode;
        }
    }

    // Метод для получения промежутка итераторов на элементы с заданным ключом
    std::pair<typename std::multiset<T>::iterator, typename std::multiset<T>::iterator> equal_range(const int& key) {
        // Используем equal_range из std::multiset
        return elements.equal_range(key);
    }

};