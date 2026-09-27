#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    int count;

public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList() { clear(); }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    void push_front(const T& val) {
        Node* n = new Node(val);
        n->next = head;
        head = n;
        ++count;
    }

    void push_back(const T& val) {
        Node* n = new Node(val);
        if (!head) {
            head = n;
        } else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = n;
        }
        ++count;
    }

    void pop_front() {
        if (empty()) throw underflow_error("List is empty");
        Node* old = head;
        head = head->next;
        delete old;
        --count;
    }

    void pop_back() {
        if (empty()) throw underflow_error("List is empty");
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* cur = head;
            while (cur->next->next) cur = cur->next;
            delete cur->next;
            cur->next = nullptr;
        }
        --count;
    }

    void insert_at(int index, const T& val) {
        if (index < 0 || index > count)
            throw out_of_range("Index out of range");
        if (index == 0) {
            push_front(val);
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; ++i) cur = cur->next;
        Node* n = new Node(val);
        n->next = cur->next;
        cur->next = n;
        ++count;
    }

    void remove_at(int index) {
        if (index < 0 || index >= count)
            throw out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; ++i) cur = cur->next;
        Node* old = cur->next;
        cur->next = old->next;
        delete old;
        --count;
    }

    void clear() {
        while (!empty()) pop_front();
    }

    T& front() {
        if (empty()) throw underflow_error("List is empty");
        return head->data;
    }

    T& back() {
        if (empty()) throw underflow_error("List is empty");
        Node* cur = head;
        while (cur->next) cur = cur->next;
        return cur->data;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count)
            throw out_of_range("Index out of range");
        Node* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    int search(const T& val) const {
        Node* cur = head;
        int idx = 0;
        while (cur) {
            if (cur->data == val) return idx;
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void print() const {
        Node* cur = head;
        cout << "[ ";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << " ]\n";
    }
};

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() { clear(); }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    void push_back(const T& val) {
        Node* n = new Node(val);
        if (!tail) {
            head = tail = n;
        } else {
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        ++count;
    }

    void push_front(const T& val) {
        Node* n = new Node(val);
        if (!head) {
            head = tail = n;
        } else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        ++count;
    }

    void pop_back() {
        if (empty()) throw underflow_error("List is empty");
        Node* old = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete old;
        --count;
    }

    void pop_front() {
        if (empty()) throw underflow_error("List is empty");
        Node* old = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete old;
        --count;
    }

    void clear() {
        while (!empty()) pop_back();
    }

    void print_forward() const {
        Node* cur = head;
        cout << "[ ";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " <-> ";
            cur = cur->next;
        }
        cout << " ]\n";
    }

    void print_backward() const {
        Node* cur = tail;
        cout << "[ ";
        while (cur) {
            cout << cur->data;
            if (cur->prev) cout << " <-> ";
            cur = cur->prev;
        }
        cout << " ] (reversed)\n";
    }
};

int main() {
    cout << "=== Singly Linked List ===\n";
    LinkedList<int> sl;
    sl.push_back(10);
    sl.push_back(20);
    sl.push_back(30);
    sl.push_front(5);
    sl.print();

    sl.insert_at(2, 15);
    sl.print();

    sl.remove_at(0);
    sl.print();

    cout << "Search 20: index " << sl.search(20) << "\n";
    sl.reverse();
    sl.print();

    cout << "\n=== Doubly Linked List ===\n";
    DoublyLinkedList<string> dl;
    dl.push_back("alpha");
    dl.push_back("beta");
    dl.push_back("gamma");
    dl.push_front("zero");
    dl.print_forward();
    dl.print_backward();

    dl.pop_back();
    dl.pop_front();
    dl.print_forward();

    return 0;
}
