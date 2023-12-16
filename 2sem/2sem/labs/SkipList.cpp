#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

template <typename T> class SkipListNode {
public:
  T value;
  std::vector<std::shared_ptr<SkipListNode<T>>> forward;
  std::vector<std::shared_ptr<SkipListNode<T>>> backward;

  SkipListNode(T val, int level)
      : value(val), forward(level, nullptr), backward(level, nullptr) {}
};

template <typename T, typename Compare = std::less<T>> class SkipList {
public:
  class iterator;
  class reverse_iterator;

private:
  int maxLevel;
  float probability;
  std::shared_ptr<SkipListNode<T>> header;
  std::shared_ptr<SkipListNode<T>> tail;
  int level;
  int elementsCount;
  std::default_random_engine generator;
  std::bernoulli_distribution distribution;
  Compare comp;

  int randomLevel() {
    int lvl = 1;
    while (((double)rand() / RAND_MAX) < probability && lvl < maxLevel - 1) {
      lvl++;
    }
    return lvl;
  }

public:
  SkipList(int maxLevel = 16, float probability = 0.5,
           const Compare &comp = Compare())
      : maxLevel(maxLevel), probability(probability), level(0),
        elementsCount(0),
        header(std::make_shared<SkipListNode<T>>(T(), maxLevel)), tail(nullptr),
        distribution(probability), comp(comp) {
    std::random_device rd;
    generator = std::default_random_engine(rd());
  }

  template <typename InputIterator>
  SkipList(InputIterator first, InputIterator last, int maxLevel = 16,
           float probability = 0.5, const Compare &comp = Compare())
      : maxLevel(maxLevel), probability(probability), level(0),
        elementsCount(0),
        header(std::make_shared<SkipListNode<T>>(T(), maxLevel)), tail(nullptr),
        distribution(probability), comp(comp) {
    std::random_device rd;
    generator = std::default_random_engine(rd());
    for (auto it = first; it != last; ++it) {
      insert(*it);
    }
  }

  SkipList(const SkipList<T, Compare> &other)
      : maxLevel(other.maxLevel), probability(other.probability),
        level(other.level), elementsCount(other.elementsCount),
        header(std::make_shared<SkipListNode<T>>(T(), maxLevel)), tail(nullptr),
        distribution(other.probability), comp(other.comp) {

    std::vector<std::shared_ptr<SkipListNode<T>>> nodes(maxLevel, header);
    auto current = other.header->forward[0];
    while (current) {
      auto newNode = std::make_shared<SkipListNode<T>>(current->value,
                                                       current->forward.size());
      for (size_t i = 0; i < current->forward.size(); ++i) {
        nodes[i]->forward[i] = newNode;
        newNode->backward[i] = nodes[i];
        nodes[i] = newNode;
      }
      if (!current->forward[0]) {
        tail = newNode;
      }
      current = current->forward[0];
    }
  }

  SkipList<T, Compare> &operator=(const SkipList<T, Compare> &other) {
    if (this != &other) {
      // Clear the current list
      clear();

      // Copy properties
      maxLevel = other.maxLevel;
      probability = other.probability;
      level = other.level;
      elementsCount = other.elementsCount;
      distribution = other.distribution;
      comp = other.comp;

      // Deep copy nodes
      std::vector<std::shared_ptr<SkipListNode<T>>> nodes(maxLevel, header);
      auto current = other.header->forward[0];
      while (current) {
        auto newNode = std::make_shared<SkipListNode<T>>(
            current->value, current->forward.size());
        for (size_t i = 0; i < current->forward.size(); ++i) {
          nodes[i]->forward[i] = newNode;
          newNode->backward[i] = nodes[i];
          nodes[i] = newNode;
        }
        if (!current->forward[0]) {
          tail = newNode;
        }
        current = current->forward[0];
      }
    }
    return *this;
  }

  SkipList(SkipList<T> &&other) noexcept
      : maxLevel(other.maxLevel), probability(other.probability),
        level(other.level), elementsCount(other.elementsCount),
        header(std::move(other.header)), tail(std::move(other.tail)),
        generator(std::move(other.generator)), distribution(other.distribution),
        comp(std::move(other.comp)) {
    other.header = nullptr;
    other.level = 0;
    other.elementsCount = 0;
  }

  SkipList<T> &operator=(SkipList<T> &&other) noexcept {
    if (this != &other) {
      maxLevel = other.maxLevel;
      probability = other.probability;
      level = other.level;
      elementsCount = other.elementsCount;
      header = std::move(other.header);
      tail = std::move(other.tail);
      generator = std::move(other.generator);
      distribution = std::move(other.distribution);
      comp = std::move(other.comp);

      other.header = nullptr;
      other.level = 0;
      other.elementsCount = 0;
    }
    return *this;
  }

  bool empty() const { return header->forward[0] == nullptr; }
  void insert(const T &value) {
    std::vector<std::shared_ptr<SkipListNode<T>>> update(maxLevel, header);
    std::shared_ptr<SkipListNode<T>> current = header;

    // Find place to insert the new node
    for (int i = level; i >= 0; --i) {
      while (current->forward[i] && comp(current->forward[i]->value, value)) {
        current = current->forward[i];
      }
      update[i] = current;
    }

    // Decide level for the new node
    int newLevel = randomLevel();
    if (newLevel > level) {
      for (int i = level + 1; i <= newLevel; ++i) {
        update[i] = header;
      }
      level = newLevel;
    }

    // Create and link the new node
    auto newNode = std::make_shared<SkipListNode<T>>(value, newLevel + 1);
    for (int i = 0; i <= newLevel; ++i) {
      newNode->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = newNode;

      // Set backward links (for reverse iteration)
      if (newNode->forward[i]) {
        newNode->forward[i]->backward[i] = newNode;
      }
      newNode->backward[i] = update[i];
    }

    elementsCount++;

    if (!newNode->forward[0]) {
      tail = newNode;
    }
  }

  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (auto it = first; it != last; ++it) {
      insert(*it); // Insert each element in the range
    }
  }

  int size() const { return elementsCount; }

  iterator find(const T &value) const {
    auto current = header;
    for (int i = level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i]->value < value) {
        current = current->forward[i];
      }
    }
    current = current->forward[0];
    if (current && current->value == value) {
      return iterator(current);
    }
    return end();
  }

  void erase(iterator pos) {
    if (pos == end() || empty())
      return; // Safety check

    std::vector<std::shared_ptr<SkipListNode<T>>> update(maxLevel, nullptr);
    auto current = header;
    auto target = pos.node; // Node to be removed

    // Find the update path
    for (int i = level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i] != target) {
        current = current->forward[i];
      }
      update[i] = current;
    }

    // Update forward pointers
    for (int i = 0; i <= level; ++i) {
      if (update[i]->forward[i] != target) {
        break;
      }
      update[i]->forward[i] = target->forward[i];
    }

    // Update backward pointers
    for (int i = 0; i <= level; ++i) {
      if (i < target->forward.size() && target->forward[i] &&
          target->forward[i]->backward[i] == target) {
        target->forward[i]->backward[i] =
            (update[i] != header) ? update[i] : nullptr;
      }
    }

    // Update tail if needed
    if (tail == target) {
      tail = update[0] != header ? update[0] : nullptr;
    }

    // Update level and elementsCount
    while (level > 0 && header->forward[level] == nullptr) {
      level--;
    }
    elementsCount--;
    if (elementsCount == 0) {
      tail = nullptr;
    }
  }

  void erase(iterator first, iterator last) {
    while (first != last) {
      auto current = first++; // Save the current iterator and move to next
      erase(current);         // Erase the element at the current iterator
    }
  }

  void clear() {
    header = std::make_shared<SkipListNode<T>>(T(), maxLevel);
    tail = nullptr;
    level = 0;
    elementsCount = 0;
  }

  iterator begin() { return iterator(header->forward[0]); }
  iterator begin() const { return iterator(header->forward[0]); }
  iterator end() { return iterator(nullptr); }
  iterator end() const { return iterator(nullptr); }
  reverse_iterator rbegin() { return reverse_iterator(tail); }
  reverse_iterator rbegin() const { return reverse_iterator(tail); }
  reverse_iterator rend() { return reverse_iterator(header); }
  reverse_iterator rend() const { return reverse_iterator(header); }

  class iterator {
  public:
    std::shared_ptr<SkipListNode<T>> node;

    // Constructor to initialize the iterator with a node
    iterator(std::shared_ptr<SkipListNode<T>> startNode) : node(startNode) {}

    // Dereference operator to access the value
    T &operator*() { return node->value; }

    const T &operator*() const { return node->value; }

    // Member access operator to access the value
    T *operator->() { return &node->value; }

    const T *operator->() const { return &node->value; }

    // Prefix increment operator to move to the next node
    iterator &operator++() {
      node = node->forward[0];
      return *this;
    }

    // Postfix increment operator to move to the next node
    iterator operator++(int) {
      iterator temp = *this;
      node = node->forward[0];
      return temp;
    }

    // Equality comparison operator
    bool operator==(const iterator &other) const { return node == other.node; }

    // Inequality comparison operator
    bool operator!=(const iterator &other) const { return node != other.node; }
  };

  class reverse_iterator {

  public:
    std::shared_ptr<SkipListNode<T>> node;
    // Constructor to initialize the reverse_iterator with a node
    reverse_iterator(std::shared_ptr<SkipListNode<T>> startNode)
        : node(startNode) {}

    // Dereference operator to access the value
    T &operator*() { return node->value; }

    const T &operator*() const { return node->value; }

    // Member access operator to access the value
    T *operator->() { return &node->value; }

    const T *operator->() const { return &node->value; }

    // Prefix decrement operator to move to the previous node
    reverse_iterator &operator--() {
      // Assuming that the node has a backward link at level 0
      node = node->backward[0];
      return *this;
    }

    // Postfix decrement operator to move to the previous node
    reverse_iterator operator--(int) {
      reverse_iterator temp = *this;
      // Assuming that the node has a backward link at level 0
      node = node->backward[0];
      return temp;
    }

    // Equality comparison operator
    bool operator==(const reverse_iterator &other) const {
      return node == other.node;
    }

    // Inequality comparison operator
    bool operator!=(const reverse_iterator &other) const {
      return node != other.node;
    }
  };

  int count(const T &value) const {
    int cnt = 0;
    auto current = header->forward[0];
    while (current && current->value <= value) {
      if (current->value == value) {
        cnt++;
      }
      current = current->forward[0];
    }
    return cnt;
  }

  iterator lower_bound(const T &value) {
    auto current = header;
    for (int i = level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i]->value < value) {
        current = current->forward[i];
      }
    }
    return iterator(current->forward[0]);
  }

  iterator upper_bound(const T &value) {
    auto current = header;
    for (int i = level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i]->value <= value) {
        current = current->forward[i];
      }
    }
    return iterator(current->forward[0]);
  }

  std::pair<iterator, iterator> equal_range(const T &value) const {
    return std::make_pair(lower_bound(value), upper_bound(value));
  }
};

int main() {
  // Create a skip list with different probabilities
  const int maxLevel = 16;
  const int numElements = 1000; // Number of elements to insert

  // Test with different probabilities
  for (float probability : {0.25f, 0.5f, 0.75f}) {
    std::cout << "Testing with probability: " << probability << std::endl;

    SkipList<int> skipList(maxLevel, probability);

    // Insert elements
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
      skipList.insert(rand() % numElements);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertDuration = end - start;
    std::cout << "Insertion time: " << insertDuration.count() << " seconds"
              << std::endl;

    // Search elements
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
      skipList.find(rand() % numElements);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> searchDuration = end - start;
    std::cout << "Search time: " << searchDuration.count() << " seconds"
              << std::endl;

    // Delete elements
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
      skipList.erase(skipList.find(rand() % numElements));
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> deleteDuration = end - start;
    std::cout << "Deletion time: " << deleteDuration.count() << " seconds"
              << std::endl;

    std::cout << "-------------------------------" << std::endl;
  }

  return 0;
}
