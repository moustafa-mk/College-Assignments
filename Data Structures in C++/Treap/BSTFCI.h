//
// Created by Moustafa on 4/27/2019.
//

#ifndef DATASTRUCTURES_ASSIGNMENT4_20170288_BSTFCI_H
#define DATASTRUCTURES_ASSIGNMENT4_20170288_BSTFCI_H

#include <vector>

template<typename T>
class BSTFCI {
private:
    class iterator;

    struct BSTNode {
        T value;
        BSTNode *left;
        BSTNode *right;
        BSTNode *parent;
        std::vector<int> lines;

        explicit BSTNode(T value);

        friend class BSTFCI<T>;

        friend class iterator;
    };

    class iterator {
    private:
        BSTNode *position;

    public:
        iterator();

        explicit iterator (BSTNode *position);

        iterator& operator= (iterator another);

        iterator& operator= (T val);

        T operator* ();

        // TODO
        /*iterator operator++ ();

        iterator operator++ ();

        iterator operator++ ();

        iterator operator++ ();*/

        ~iterator();

        friend class BSTFCI<T>;

        friend class indexBuilder;
    };

    BSTNode *root;

    int sz = 0;
public:

    BSTFCI();

    explicit BSTFCI(T value);

    explicit BSTFCI(BSTNode *root);

    iterator insert(T value);

    iterator search(T value);
    iterator erase(T value);

    iterator erase(iterator it);
    iterator Min_Elem(iterator it);

    iterator Max_Elem(iterator it);

    int height(BSTNode *node);
    bool isBalanced();

    bool isBalanced(BSTNode *root);

    template <typename K>
    friend bool isSubTree(BSTFCI<K> *t1, BSTFCI<K> *t2);

    /*template <typename K>
    friend bool areIdentical(BSTNode *node1, BSTNode *node2);*/

    template <typename K>
    friend bool areIdentical(typename BSTFCI<K>::BSTNode *node1, typename BSTFCI<K>::BSTNode *node2);
    void printRange(T val1, T val2);

    void traverse(T val1, T val2, std::vector<T> &vec, BSTNode *node);
    void flip() { flip(root); }

    void flip(BSTNode *node);

    iterator operator[](T value);

    int size();
    void inorder();

    void inorder(BSTNode *node);

    void clear() { clear(root); }

    void clear(BSTNode *node);

    iterator begin() { return iterator(root); }

    ~BSTFCI();

    friend class indexBuilder;
};

#endif //DATASTRUCTURES_ASSIGNMENT4_20170288_BSTFCI_H
