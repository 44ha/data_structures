#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    int sz;
    int cap;

    void grow() {
        int newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];
        for (int i = 0; i < sz; ++i)
            newData[i] = move(data[i]);
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    DynamicArray() : data(nullptr), sz(0), cap(0) {}

    DynamicArray(int n, const T& val = T{}) : sz(n), cap(n) {
        data = new T[cap];
        for (int i = 0; i < sz; ++i) data[i] = val;
    }

    DynamicArray(initializer_list<T> il) : sz(0), cap(il.size()) {
        data = new T[cap];
        for (const T& v : il) data[sz++] = v;
    }

    DynamicArray(const DynamicArray& other) : sz(other.sz), cap(other.cap) {
        data = new T[cap];
        for (int i = 0; i < sz; ++i) data[i] = other.data[i];
    }

    DynamicArray& operator=(DynamicArray other) {
        swap(data, other.data);
        swap(sz, other.sz);
        swap(cap, other.cap);
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    int size() const { return sz; }
    int capacity() const { return cap; }
    bool empty() const { return sz == 0; }

    void reserve(int newCap) {
        if (newCap <= cap) return;
        T* newData = new T[newCap];
        for (int i = 0; i < sz; ++i) newData[i] = move(data[i]);
        delete[] data;
        data = newData;
        cap = newCap;
    }

    void resize(int newSz, const T& val = T{}) {
        if (newSz > cap) reserve(newSz);
        for (int i = sz; i < newSz; ++i) data[i] = val;
        sz = newSz;
    }

    T& operator[](int i) { return data[i]; }
    const T& operator[](int i) const { return data[i]; }

    T& at(int i) {
        if (i < 0 || i >= sz) throw out_of_range("Index out of range");
        return data[i];
    }

    T& front() { return data[0]; }
    T& back() { return data[sz - 1]; }

    void push_back(const T& val) {
        if (sz == cap) grow();
        data[sz++] = val;
    }

    void pop_back() {
        if (empty()) throw underflow_error("Array is empty");
        --sz;
    }

    void insert(int idx, const T& val) {
        if (idx < 0 || idx > sz) throw out_of_range("Index out of range");
        if (sz == cap) grow();
        for (int i = sz; i > idx; --i) data[i] = move(data[i - 1]);
        data[idx] = val;
        ++sz;
    }

    void erase(int idx) {
        if (idx < 0 || idx >= sz) throw out_of_range("Index out of range");
        for (int i = idx; i < sz - 1; ++i) data[i] = move(data[i + 1]);
        --sz;
    }

    void clear() { sz = 0; }

    int find(const T& val) const {
        for (int i = 0; i < sz; ++i)
            if (data[i] == val) return i;
        return -1;
    }

    void sort() {
        sort(data, data + sz);
    }

    int binarySearch(const T& val) const {
        int lo = 0, hi = sz - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (data[mid] == val) return mid;
            else if (data[mid] < val) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }

    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }

    void print() const {
        cout << "[ ";
        for (int i = 0; i < sz; ++i) {
            cout << data[i];
            if (i < sz - 1) cout << ", ";
        }
        cout << " ]  (size=" << sz << ", cap=" << cap << ")\n";
    }
};

int main() {
    cout << "=== Dynamic Array ===\n";
    DynamicArray<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    arr.print();

    arr.push_back(100);
    arr.insert(0, -1);
    arr.print();

    arr.erase(0);
    arr.pop_back();
    arr.print();

    cout << "front=" << arr.front()
         << " back=" << arr.back()
         << " size=" << arr.size() << "\n";

    cout << "Iteration: ";
    for (int v : arr) cout << v << " ";
    cout << "\n";

    cout << "Find 9 at index: " << arr.find(9) << "\n";

    arr.sort();
    arr.print();
    cout << "Binary search 5: index " << arr.binarySearch(5) << "\n";
    cout << "Binary search 7: index " << arr.binarySearch(7) << "\n";

    DynamicArray<int> sized(5, 0);
    sized.resize(8, 42);
    sized.print();

    return 0;
}
