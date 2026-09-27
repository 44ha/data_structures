#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* topNode;
    int count;

public:
    Stack() : topNode(nullptr), count(0) {}
    ~Stack() { while (!empty()) pop(); }

    void push(const T& val) {
        Node* n = new Node(val);
        n->next = topNode;
        topNode = n;
        ++count;
    }

    void pop() {
        if (empty()) throw underflow_error("Stack underflow");
        Node* old = topNode;
        topNode = topNode->next;
        delete old;
        --count;
    }

    T& top() {
        if (empty()) throw underflow_error("Stack is empty");
        return topNode->data;
    }

    bool empty() const { return count == 0; }
    int size() const { return count; }

    void print() const {
        Node* cur = topNode;
        cout << "Stack (top -> bottom): ";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " | ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* frontNode;
    Node* backNode;
    int count;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), count(0) {}
    ~Queue() { while (!empty()) dequeue(); }

    void enqueue(const T& val) {
        Node* n = new Node(val);
        if (!backNode) { frontNode = backNode = n; }
        else { backNode->next = n; backNode = n; }
        ++count;
    }

    void dequeue() {
        if (empty()) throw underflow_error("Queue underflow");
        Node* old = frontNode;
        frontNode = frontNode->next;
        if (!frontNode) backNode = nullptr;
        delete old;
        --count;
    }

    T& front() {
        if (empty()) throw underflow_error("Queue is empty");
        return frontNode->data;
    }

    T& back() {
        if (empty()) throw underflow_error("Queue is empty");
        return backNode->data;
    }

    bool empty() const { return count == 0; }
    int size() const { return count; }

    void print() const {
        Node* cur = frontNode;
        cout << "Queue (front -> back): ";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " | ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* frontNode;
    Node* backNode;
    int count;

public:
    Deque() : frontNode(nullptr), backNode(nullptr), count(0) {}
    ~Deque() { while (!empty()) pop_front(); }

    void push_front(const T& val) {
        Node* n = new Node(val);
        if (!frontNode) { frontNode = backNode = n; }
        else {
            n->next = frontNode;
            frontNode->prev = n;
            frontNode = n;
        }
        ++count;
    }

    void push_back(const T& val) {
        Node* n = new Node(val);
        if (!backNode) { frontNode = backNode = n; }
        else {
            n->prev = backNode;
            backNode->next = n;
            backNode = n;
        }
        ++count;
    }

    void pop_front() {
        if (empty()) throw underflow_error("Deque is empty");
        Node* old = frontNode;
        frontNode = frontNode->next;
        if (frontNode) frontNode->prev = nullptr;
        else backNode = nullptr;
        delete old;
        --count;
    }

    void pop_back() {
        if (empty()) throw underflow_error("Deque is empty");
        Node* old = backNode;
        backNode = backNode->prev;
        if (backNode) backNode->next = nullptr;
        else frontNode = nullptr;
        delete old;
        --count;
    }

    T& front() {
        if (empty()) throw underflow_error("Deque is empty");
        return frontNode->data;
    }

    T& back() {
        if (empty()) throw underflow_error("Deque is empty");
        return backNode->data;
    }

    bool empty() const { return count == 0; }
    int size() const { return count; }

    void print() const {
        Node* cur = frontNode;
        cout << "Deque [front <-> back]: ";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " <-> ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

int main() {
    cout << "=== Stack ===\n";
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.print();
    cout << "Top: " << s.top() << "\n";
    s.pop();
    s.print();

    cout << "\n=== Queue ===\n";
    Queue<string> q;
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");
    q.print();
    cout << "Front: " << q.front() << "\n";
    q.dequeue();
    q.print();

    cout << "\n=== Deque ===\n";
    Deque<int> dq;
    dq.push_back(2);
    dq.push_back(3);
    dq.push_front(1);
    dq.push_front(0);
    dq.print();
    dq.pop_front();
    dq.pop_back();
    dq.print();

    return 0;
}
