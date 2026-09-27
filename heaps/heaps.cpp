#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename T>
class MaxHeap {
private:
    vector<T> data;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && data[parent(i)] < data[i]) {
            swap(data[parent(i)], data[i]);
            i = parent(i);
        }
    }

    void siftDown(int i, int heapSize) {
        int largest = i;
        int l = left(i), r = right(i);
        if (l < heapSize && data[l] > data[largest]) largest = l;
        if (r < heapSize && data[r] > data[largest]) largest = r;
        if (largest != i) {
            swap(data[i], data[largest]);
            siftDown(largest, heapSize);
        }
    }

public:
    MaxHeap() = default;

    explicit MaxHeap(vector<T> arr) : data(move(arr)) {
        for (int i = (int)data.size() / 2 - 1; i >= 0; --i)
            siftDown(i, data.size());
    }

    void push(const T& val) {
        data.push_back(val);
        siftUp(data.size() - 1);
    }

    void pop() {
        if (empty()) throw underflow_error("Heap is empty");
        data[0] = data.back();
        data.pop_back();
        if (!empty()) siftDown(0, data.size());
    }

    const T& top() const {
        if (empty()) throw underflow_error("Heap is empty");
        return data[0];
    }

    bool empty() const { return data.empty(); }
    int size() const { return (int)data.size(); }

    void print() const {
        cout << "MaxHeap: ";
        for (const T& v : data) cout << v << " ";
        cout << "\n";
    }
};

template <typename T>
class MinHeap {
private:
    vector<T> data;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && data[parent(i)] > data[i]) {
            swap(data[parent(i)], data[i]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int smallest = i;
        int l = left(i), r = right(i), n = data.size();
        if (l < n && data[l] < data[smallest]) smallest = l;
        if (r < n && data[r] < data[smallest]) smallest = r;
        if (smallest != i) {
            swap(data[i], data[smallest]);
            siftDown(smallest);
        }
    }

public:
    MinHeap() = default;

    void push(const T& val) {
        data.push_back(val);
        siftUp(data.size() - 1);
    }

    void pop() {
        if (empty()) throw underflow_error("Heap is empty");
        data[0] = data.back();
        data.pop_back();
        if (!empty()) siftDown(0);
    }

    const T& top() const {
        if (empty()) throw underflow_error("Heap is empty");
        return data[0];
    }

    bool empty() const { return data.empty(); }
    int size() const { return (int)data.size(); }

    void print() const {
        cout << "MinHeap: ";
        for (const T& v : data) cout << v << " ";
        cout << "\n";
    }
};

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        int pos = i;
        while (true) {
            int largest = pos;
            int l = 2 * pos + 1, r = 2 * pos + 2;
            if (l < n && arr[l] > arr[largest]) largest = l;
            if (r < n && arr[r] > arr[largest]) largest = r;
            if (largest == pos) break;
            swap(arr[pos], arr[largest]);
            pos = largest;
        }
    }

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        int pos = 0, heapSz = i;
        while (true) {
            int largest = pos;
            int l = 2 * pos + 1, r = 2 * pos + 2;
            if (l < heapSz && arr[l] > arr[largest]) largest = l;
            if (r < heapSz && arr[r] > arr[largest]) largest = r;
            if (largest == pos) break;
            swap(arr[pos], arr[largest]);
            pos = largest;
        }
    }
}

template <typename T>
using PriorityQueue = MinHeap<T>;

int main() {
    cout << "=== Max-Heap ===\n";
    MaxHeap<int> maxH;
    for (int v : {3, 1, 6, 5, 2, 4}) maxH.push(v);
    maxH.print();
    cout << "Top: " << maxH.top() << "\n";
    maxH.pop();
    maxH.print();
    cout << "Top after pop: " << maxH.top() << "\n";

    cout << "\n=== Min-Heap ===\n";
    MinHeap<int> minH;
    for (int v : {3, 1, 6, 5, 2, 4}) minH.push(v);
    minH.print();
    cout << "Top: " << minH.top() << "\n";
    minH.pop();
    minH.print();
    cout << "Top after pop: " << minH.top() << "\n";

    cout << "\n=== Build Max-Heap from vector (heapify) ===\n";
    MaxHeap<int> built(vector<int>{9, 4, 7, 2, 8, 1});
    built.print();

    cout << "\n=== Heap Sort ===\n";
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    cout << "Before: ";
    for (int v : arr) cout << v << " ";
    cout << "\n";
    heapSort(arr);
    cout << "After:  ";
    for (int v : arr) cout << v << " ";
    cout << "\n";

    cout << "\n=== Priority Queue (min-priority) ===\n";
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(1);
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";

    return 0;
}
