#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <stdexcept>

using namespace std;

template <typename K, typename V>
class HashTableChaining {
private:
    using Bucket = list<pair<K, V>>;
    vector<Bucket> table;
    int capacity;
    int itemCount;

    int hashIndex(const K& key) const {
        return (int)(hash<K>{}(key) % (size_t)capacity);
    }

    void rehash() {
        int oldCap = capacity;
        capacity = oldCap * 2;
        vector<Bucket> newTable(capacity);

        for (auto& bucket : table)
            for (auto& [k, v] : bucket) {
                int idx = (int)(hash<K>{}(k) % (size_t)capacity);
                newTable[idx].push_back({k, v});
            }

        table = move(newTable);
    }

public:
    HashTableChaining(int cap = 8) : capacity(cap), itemCount(0), table(cap) {}

    void insert(const K& key, const V& val) {
        int idx = hashIndex(key);
        for (auto& [k, v] : table[idx]) {
            if (k == key) {
                v = val;
                return;
            }
        }
        table[idx].push_back({key, val});
        ++itemCount;
        if ((double)itemCount / capacity > 0.75) rehash();
    }

    bool search(const K& key, V& outVal) const {
        int idx = hashIndex(key);
        for (const auto& [k, v] : table[idx])
            if (k == key) { outVal = v; return true; }
        return false;
    }

    V& at(const K& key) {
        int idx = hashIndex(key);
        for (auto& [k, v] : table[idx])
            if (k == key) return v;
        throw out_of_range("Key not found");
    }

    bool remove(const K& key) {
        int idx = hashIndex(key);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --itemCount;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const {
        V dummy;
        return search(key, dummy);
    }

    double loadFactor() const { return (double)itemCount / capacity; }
    int size() const { return itemCount; }
    bool empty() const { return itemCount == 0; }

    void print() const {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].empty()) continue;
            cout << "[" << i << "] ";
            for (const auto& [k, v] : table[i])
                cout << "{" << k << ": " << v << "} ";
            cout << "\n";
        }
    }
};

template <typename K, typename V>
class HashTableLinearProbe {
private:
    enum class State { EMPTY, OCCUPIED, DELETED };
    struct Slot {
        K key;
        V val;
        State state = State::EMPTY;
    };

    vector<Slot> table;
    int capacity;
    int itemCount;

    int hashIndex(const K& key) const {
        return (int)(hash<K>{}(key) % (size_t)capacity);
    }

    void rehash() {
        vector<Slot> old = table;
        capacity *= 2;
        table.assign(capacity, Slot{});
        itemCount = 0;
        for (auto& slot : old)
            if (slot.state == State::OCCUPIED) insert(slot.key, slot.val);
    }

public:
    HashTableLinearProbe(int cap = 8) : capacity(cap), itemCount(0), table(cap) {}

    void insert(const K& key, const V& val) {
        if ((double)itemCount / capacity > 0.65) rehash();
        int idx = hashIndex(key);
        for (int i = 0; i < capacity; ++i) {
            int probe = (idx + i) % capacity;
            if (table[probe].state != State::OCCUPIED) {
                table[probe] = {key, val, State::OCCUPIED};
                ++itemCount;
                return;
            }
            if (table[probe].key == key) {
                table[probe].val = val;
                return;
            }
        }
    }

    bool search(const K& key, V& outVal) const {
        int idx = hashIndex(key);
        for (int i = 0; i < capacity; ++i) {
            int probe = (idx + i) % capacity;
            if (table[probe].state == State::EMPTY) return false;
            if (table[probe].state == State::OCCUPIED && table[probe].key == key) {
                outVal = table[probe].val;
                return true;
            }
        }
        return false;
    }

    bool remove(const K& key) {
        int idx = hashIndex(key);
        for (int i = 0; i < capacity; ++i) {
            int probe = (idx + i) % capacity;
            if (table[probe].state == State::EMPTY) return false;
            if (table[probe].state == State::OCCUPIED && table[probe].key == key) {
                table[probe].state = State::DELETED;
                --itemCount;
                return true;
            }
        }
        return false;
    }

    int size() const { return itemCount; }
    bool empty() const { return itemCount == 0; }

    void print() const {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].state != State::OCCUPIED) continue;
            cout << "[" << i << "] {" << table[i].key
                 << ": " << table[i].val << "}\n";
        }
    }
};

int main() {
    cout << "=== Hash Table (Separate Chaining) ===\n";
    HashTableChaining<string, int> ht;
    ht.insert("apple", 5);
    ht.insert("banana", 3);
    ht.insert("cherry", 8);
    ht.insert("date", 2);
    ht.insert("elderberry", 11);
    ht.print();

    int val;
    if (ht.search("banana", val))
        cout << "Found banana: " << val << "\n";

    ht.insert("banana", 99);
    cout << "Updated banana: " << ht.at("banana") << "\n";

    ht.remove("cherry");
    cout << "After removing cherry: "
         << (ht.contains("cherry") ? "found" : "not found") << "\n";

    cout << "Load factor: " << ht.loadFactor() << "\n";
    cout << "Size: " << ht.size() << "\n";

    cout << "\n=== Hash Table (Linear Probing) ===\n";
    HashTableLinearProbe<int, string> lp;
    lp.insert(1, "one");
    lp.insert(9, "nine");
    lp.insert(17, "seventeen");
    lp.insert(5, "five");
    lp.insert(13, "thirteen");
    lp.print();

    string found;
    if (lp.search(17, found))
        cout << "Found 17: " << found << "\n";

    lp.remove(9);
    cout << "Search 9 after remove: "
         << (lp.search(9, found) ? found : "not found") << "\n";

    return 0;
}
