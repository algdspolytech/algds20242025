#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class HashTable {
private:
    static const int TABLE_SIZE = 1000;
    std::vector<std::list<int>> table;

    size_t hash(int key) const {
        return static_cast<size_t>(key) % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(int key) {
        size_t index = hash(key);
        auto& bucket = table[index];

        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(key);
        }
    }

    void remove(int key) {
        size_t index = hash(key);
        auto& bucket = table[index];
        bucket.remove(key);
    }

    bool search(int key) const {
        size_t index = hash(key);
        const auto& bucket = table[index];
        return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
    }
};

int main() {
    HashTable ht;
    char command;
    int key;

    while (std::cin >> command >> key) {
        switch (command) {
            case 'a':
                ht.insert(key);
                break;
            case 'r':
                ht.remove(key);
                break;
            case 'f':
                std::cout << (ht.search(key) ? "yes" : "no") << std::endl;
                break;
            default:
                std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}
