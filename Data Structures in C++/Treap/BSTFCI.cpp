//
// Created by Moustafa on 4/27/2019.
//

#include <iostream>
#include <windef.h>
#include <vector>
#include <algorithm>
#include "BSTFCI.h"

template<typename T>
BSTFCI<T>::BSTNode::BSTNode(T value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
}

template<typename T>
BSTFCI<T>::BSTFCI(BSTFCI::BSTNode *root) { this->root = root; }

template<typename T>
BSTFCI<T>::iterator::iterator() { position = nullptr; }

template<typename T>
BSTFCI<T>::iterator::iterator(BSTFCI::BSTNode *position) { this->position = position; }

template<typename T>
typename BSTFCI<T>::iterator& BSTFCI<T>::iterator::operator=(iterator another) {
    position = new BSTNode(another.position->value);
    position->left = another.position->left;
    position->right = another.position->right;
    return *this;
}

template<typename T>
typename BSTFCI<T>::iterator& BSTFCI<T>::iterator::operator=(T val) {
    if(position) delete position;
    position = new BSTNode(val);
    return *this;
}

template<typename T>
T BSTFCI<T>::iterator::operator*() { return position->value; }

template<typename T>
BSTFCI<T>::iterator::~iterator() { position = nullptr; delete position; }

template<typename T>
BSTFCI<T>::BSTFCI() { root = nullptr; }

template<typename T>
BSTFCI<T>::BSTFCI(T value) { root = new BSTNode(value), sz = 1; }

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::insert(T value) {
    if(sz == 0) {
        root = new BSTNode(value);
        sz++;
        return iterator(root);
    }
    else {
        BSTNode *current = root;
        while(true) {
            if(current->value == value) {
                break;
            } else if(current->value < value) {
                if(current->right == nullptr) {
                    current->right = new BSTNode(value);
                    current->right->parent = current;
                    current = current->right;
                    sz++;
                    break;
                } else {
                    current = current->right;
                }
            } else if(current->value > value) {
                if(current->left == nullptr) {
                    current->left = new BSTNode(value);
                    current->left->parent = current;
                    current = current->left;
                    sz++;
                    break;
                } else {
                    current = current->left;
                }
            }
        }

        return iterator(current);
    }
}

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::search(T value) {
    if(!sz)
        return iterator();
    BSTNode *current = root;
    while(true) {
        if(current->value < value) {
            if(current->right != nullptr) {
                current = current->right;
                continue;
            } else {
                return iterator(root);
            }
        } else if(current->value > value) {
            if(current->left != nullptr) {
                current = current->left;
                continue;
            } else {
                return iterator(root);
            }
        } else if(current->value == value) {
            return iterator(current);
        } else {
            return iterator(root);
        }
    }
}

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::erase(T value) {
    auto it = search(value);
    if(*it == value) {
        return erase(it);
    } else {
        return iterator(root);
    }
}

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::erase(BSTFCI::iterator it) {
    sz--;
    if(it.position->right != nullptr) {
        auto succ = Min_Elem(iterator(it.position->right));
        it.position->value = succ.position->value;
        it.position->left = succ.position->left;
        it.position->right = succ.position->right;
        erase(succ);
        return it;
    } else if(it.position->left != nullptr) {
        auto succ = Max_Elem(iterator(it.position->left));
        it.position->value = succ.position->value;
        it.position->left = succ.position->left;
        it.position->right = succ.position->right;
        erase(succ);
        return it;
    } else {
        if(it.position->parent != nullptr) {
            if (*it < it.position->parent->value)
                it.position->parent->left = nullptr;
            else
                it.position->parent->right = nullptr;
        }
        delete it.position;
        return iterator(root);
    }
}

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::Min_Elem(BSTFCI::iterator it) {
    if(it.position->left != nullptr)
        return Min_Elem(iterator(it.position->left));
    return it;
}

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::Max_Elem(BSTFCI::iterator it) {
    if(it.position->right != nullptr)
        return Min_Elem(iterator(it.position->right));
    return it;
}

template<typename T>
int BSTFCI<T>::height(BSTNode *node) {
    if(node == nullptr)
        return 0;
    return 1 + std::max(height(node->right), height(node->left));
}

template<typename T>
bool BSTFCI<T>::isBalanced() {
    return isBalanced(root);
}

template<typename T>
bool BSTFCI<T>::isBalanced(BSTFCI::BSTNode *root) {
    if(root == nullptr)
        return true;
    int lh = height(root->left), rh = height(root->right);
    return abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

template<typename T>
void BSTFCI<T>::printRange(T val1, T val2) {
    std::vector<T> vec;
    traverse(val1, val2, vec, root);
    std::sort(vec.begin(), vec.end());
    for(const auto &i : vec) std::cout << i << ' ';
    std::cout << '\n';
}

template<typename T>
void BSTFCI<T>::traverse(T val1, T val2, std::vector<T> &vec, BSTNode *node) {
    if(node == nullptr)
        return;
    if(node->value >= val1 && node->value <= val2) {
        vec.push_back(node->value);
        traverse(val1, val2, vec, node->left);
        traverse(val1, val2, vec, node->right);
    } else if(node->value > val2) {
        traverse(val1, val2, vec, node->left);
    } else {
        traverse(val1, val2, vec, node->right);
    }
}

template<typename T>
void BSTFCI<T>::flip(BSTFCI::BSTNode *node) {
    if(node == nullptr)
        return;
    auto temp = node->right;
    node->right = node->left;
    node->left = temp;
    temp = nullptr;
    delete temp;
    flip(node->left);
    flip(node->right);
}

template<typename T>
typename BSTFCI<T>::iterator BSTFCI<T>::operator[](T value) {
    return BSTFCI::iterator();
}

template<typename T>
bool areIdentical(typename BSTFCI<T>::BSTNode *node1, typename BSTFCI<T>::BSTNode *node2);

template<typename T>
bool isSubTree(BSTFCI<T> *t1, BSTFCI<T> *t2) {
    if(t2->root == nullptr)
        return true;
    if(t1->root == nullptr)
        return false;
    if(areIdentical<T>(t1->root, t2->root))
        return true;
    auto *t3 = new BSTFCI<T>(t1->root->left);
    auto *t4 = new BSTFCI<T>(t1->root->right);
    return isSubTree(t3, t2) || isSubTree(t4, t2);
}

template<typename T>
bool areIdentical(typename BSTFCI<T>::BSTNode *node1, typename BSTFCI<T>::BSTNode *node2) {
    if(node1 == nullptr && node2 == nullptr)
        return true;
    if(node1 == nullptr || node2 == nullptr)
        return false;

    return node1->value == node2->value && areIdentical<T>(node1->left, node2->left) && areIdentical<T>(node1->right, node2->right);
}

template<typename T>
int BSTFCI<T>::size() { return sz; }

template<typename T>
void BSTFCI<T>::inorder() {
    inorder(root);
    std::cout << '\n';
}

template<typename T>
void BSTFCI<T>::inorder(BSTNode *node) {
    if(!sz) return;
    if(node->left != nullptr)   inorder(node->left);
    std::cout << node->value << " ";
    if(node->right != nullptr)  inorder(node->right);
}

template<typename T>
void BSTFCI<T>::clear(BSTFCI::BSTNode *node) {
    sz = 0;
    if(node->left)
        clear(node->left);
    if(node->right)
        clear(node->right);
    delete node;
}

template<typename T>
BSTFCI<T>::~BSTFCI() {
    clear();
}

template class BSTFCI<int>;
template class BSTFCI<std::string>;
template bool isSubTree<int>(BSTFCI<int> *t1, BSTFCI<int> *t2);
template bool areIdentical<int>(typename BSTFCI<int>::BSTNode *node1, typename BSTFCI<int>::BSTNode *node2);