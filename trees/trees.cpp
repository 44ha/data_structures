#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    Node* findMin(Node* node) const {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = remove(node->left, val);
        else if (val > node->data) node->right = remove(node->right, val);
        else {
            if (!node->left) { Node* r = node->right; delete node; return r; }
            if (!node->right) { Node* l = node->left; delete node; return l; }
            Node* succ = findMin(node->right);
            node->data = succ->data;
            node->right = remove(node->right, succ->data);
        }
        return node;
    }

    bool search(Node* node, const T& val) const {
        if (!node) return false;
        if (val == node->data) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    int height(Node* node) const {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& val) { root = insert(root, val); }
    void remove(const T& val) { root = remove(root, val); }
    bool search(const T& val) const { return search(root, val); }
    int height() const { return height(root); }

    T minVal() const { return findMin(root)->data; }
    T maxVal() const {
        Node* cur = root;
        while (cur->right) cur = cur->right;
        return cur->data;
    }

    void inorder() const { cout << "In-order : "; inorder(root); cout << "\n"; }
    void preorder() const { cout << "Pre-order : "; preorder(root); cout << "\n"; }
    void postorder() const { cout << "Post-order : "; postorder(root); cout << "\n"; }

    void levelOrder() const {
        if (!root) return;
        cout << "Level-order: ";
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            cout << cur->data << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << "\n";
    }
};

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        Node(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* n) const { return n ? n->height : 0; }

    int balanceFactor(Node* n) const {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        if (n) n->height = 1 + max(height(n->left), height(n->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1) {
            if (balanceFactor(n->left) < 0) n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balanceFactor(n->right) > 0) n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insert(Node* n, const T& val) {
        if (!n) return new Node(val);
        if (val < n->data) n->left = insert(n->left, val);
        else if (val > n->data) n->right = insert(n->right, val);
        else return n;
        return balance(n);
    }

    Node* findMin(Node* n) const {
        while (n->left) n = n->left;
        return n;
    }

    Node* remove(Node* n, const T& val) {
        if (!n) return nullptr;
        if (val < n->data) n->left = remove(n->left, val);
        else if (val > n->data) n->right = remove(n->right, val);
        else {
            if (!n->left || !n->right) {
                Node* child = n->left ? n->left : n->right;
                delete n;
                return child;
            }
            Node* succ = findMin(n->right);
            n->data = succ->data;
            n->right = remove(n->right, succ->data);
        }
        return balance(n);
    }

    void inorder(Node* n) const {
        if (!n) return;
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }

    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(const T& val) { root = insert(root, val); }
    void remove(const T& val) { root = remove(root, val); }

    void inorder() const {
        cout << "AVL in-order: ";
        inorder(root);
        cout << "\n";
    }

    int height() const { return height(root); }
};

int main() {
    cout << "=== Binary Search Tree ===\n";
    BST<int> bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80})
        bst.insert(v);

    bst.inorder();
    bst.preorder();
    bst.postorder();
    bst.levelOrder();

    cout << "Height  : " << bst.height() << "\n";
    cout << "Min     : " << bst.minVal() << "\n";
    cout << "Max     : " << bst.maxVal() << "\n";
    cout << "Search 40: " << (bst.search(40) ? "found" : "not found") << "\n";

    bst.remove(30);
    bst.inorder();

    cout << "\n=== AVL Tree ===\n";
    AVLTree<int> avl;
    for (int v : {10, 20, 30, 40, 50, 25})
        avl.insert(v);
    avl.inorder();
    cout << "Height : " << avl.height() << "\n";
    avl.remove(30);
    avl.inorder();

    return 0;
}
