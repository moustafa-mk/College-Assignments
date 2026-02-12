#ifndef TREAP_H_
#define TREAP_H_

#include <iostream>

template<class T, class V>
class Treap {
public:
    class Node {
    public:
        Node *left = nullptr, *right = nullptr;
        T key;
        V value;
        int priority{};

        Node() = default;
        Node(const T &k, const V &v);
        friend std::ostream& operator<<(std::ostream &o, Treap<T, V>::Node root);
    };
private:
    Node* root;

    Node* rotateRight(Node* Q);
    Node* rotateLeft(Node* P);
    Node* balance(Node* root);
    Node* insert(Node* root, T k, V v);
    V find(Node* node, T k);
public:
    Treap() { root = nullptr; };
    void insert(T k, V v) {
        if(root == nullptr) {
            root = new Node;
            root->key = k;
            root->value = v;
            root->priority = rand()%100;
            root->left = root->right = nullptr;
            return;
        }
        insert(root, k, v);
    }
    V find(T k) { return find(root, k); }
    friend std::ostream& operator<<(std::ostream &o, Treap<T, V> tree) { o << tree.root; }
};

#endif /* TREAP_H_ */
