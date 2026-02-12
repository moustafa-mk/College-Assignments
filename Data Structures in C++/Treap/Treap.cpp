//
// Created by Moustafa on 5/2/2019.
//

#include "Treap.h"

template<class T, class V>
typename Treap<T, V>::Node *Treap<T, V>::rotateRight(Treap::Node *Q) {
    Node *x = Q->left,  *T2 = x->right;

    x->right = Q;
    Q->left = T2;

    return x;
}

template<class T, class V>
typename Treap<T, V>::Node *Treap<T, V>::rotateLeft(Treap::Node *P) {
    Node *y = P->right, *T2 = y->left;

    y->left = P;
    P->right = T2;

    return y;
}

template<class T, class V>
typename Treap<T, V>::Node *Treap<T, V>::balance(Treap::Node *root) {
    if(root->left && root->left->priority > root->priority)
        root = rotateRight(root);
    if(root->right && root->right->priority > root->priority)
        root - rotateLeft(root);
    if(root->left)
        balance(root->left);
    if(root->right)
        balance(root->right);
    return this->root;
}

template<class T, class V>
typename Treap<T, V>::Node *Treap<T, V>::insert(Treap::Node *root, T k, V v) {
    if (!this->root) {
        Node *node = new Node;
        node->key = k;
        node->value = v;
        node->priority = rand()%100;
        node->left = node->right = nullptr;
        this->root = node;
        return this->root;
    }

    if(!root) {
        Node *node = new Node(k, v);
        return node;
    }

    if (k <= root->key) {
        // Insert in left subtree
        root->left = insert(root->left, k, v);

        if (root->left->priority > root->priority)
            root = rotateRight(root);
    } else {
        root->right = insert(root->right, k, v);

        if (root->right->priority > root->priority)
            root = rotateLeft(root);
    }
    return root;
}

template<class T, class V>
V Treap<T, V>::find(Treap::Node *node, T k) {
    if (node == nullptr || node->key == k)
        return k;

    if (node->key < k)
        return find(node->right, k);

    return find(node->left, k);
}

template <typename T, typename V>
std::ostream &operator<<(std::ostream &o, typename Treap<T, V>::Node root) {
    if(root)
        o << root.left << root.key << '\t' << root.value << '\n' << root.right;
}

template<class T, class V>
Treap<T, V>::Node::Node(const T &k, const V &v) {
    key = k;
    value = v;
    priority = rand()%100;
    left = right = NULL;
}

template class Treap<std::string, std::string>;
