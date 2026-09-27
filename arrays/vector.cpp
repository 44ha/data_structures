#include <iostream>
using namespace std;

template<typename ElementType>
class SimpleVector {
private:
    ElementType* elements;
    int currentSize;
    int maxCapacity;

    void expandCapacity() {
        maxCapacity *= 2;
        ElementType* newElements = new ElementType[maxCapacity];
        for (int i = 0; i < currentSize; ++i)
            newElements[i] = elements[i];
        delete[] elements;
        elements = newElements;
    }

public:
    SimpleVector() {
        maxCapacity = 2;
        currentSize = 0;
        elements = new ElementType[maxCapacity];
    }

    ~SimpleVector() {
        delete[] elements;
    }

    void add(const ElementType& value) {
        if (currentSize == maxCapacity)
            expandCapacity();
        elements[currentSize++] = value;
    }

    void removeLast() {
        if (currentSize > 0)
            currentSize--;
    }

    int size() const {
        return currentSize;
    }

    int capacity() const {
        return maxCapacity;
    }

    ElementType& operator[](int index) {
        return elements[index];
    }

    class Iterator {
    private:
        ElementType* currentPtr;
    public:
        Iterator(ElementType* ptr) : currentPtr(ptr) {}

        ElementType& operator*() {
            return *currentPtr;
        }

        Iterator& operator++() {
            ++currentPtr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++currentPtr;
            return temp;
        }

        bool operator!=(const Iterator& other) {
            return currentPtr != other.currentPtr;
        }
    };

    Iterator begin() {
        return Iterator(elements);
    }

    Iterator end() {
        return Iterator(elements + currentSize);
    }
};

int main() {
    SimpleVector<int> numbers;

    numbers.add(10);
    numbers.add(20);
    numbers.add(30);

    for (SimpleVector<int>::Iterator it = numbers.begin(); it != numbers.end(); it++)
        cout << *it << " ";

    cout << "\nSize: " << numbers.size() << ", Capacity: " << numbers.capacity() << endl;

    return 0;
}
