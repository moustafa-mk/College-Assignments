//
// Created by Moustafa on 13-Apr-19.
//

#ifndef LINKED_LIST_LIST_H
#define LINKED_LIST_LIST_H

#include <unordered_map>

template<typename T>
class List {
public:

    class Iterator;

    struct Node {
        T data;
        Node *next;
        Node *prev;

        friend class List;

        friend class Iterator;
    };

    class Iterator {
    private:
        Node *position;

        friend class List;

    public:
        Iterator();

        explicit Iterator(Node *);

        void operator++();

        void operator++(int);

        void operator--();

        T &operator*();

        bool operator==(const Iterator &);

        bool operator!=(const Iterator &);
    };

private:
    Node *dummy = NULL;
    Node *head = NULL;
    Node *tail = NULL;
    int _size;

public:
    List();

    List(T value, int initial_size);

    List(const List<T> &another);

    List &operator=(List list);

    virtual ~List();

    int size() { return _size; }

    Iterator begin() { return Iterator(head != NULL ? head : dummy); }

    Iterator end() { return Iterator(dummy); }

    Iterator erase(Iterator _iter);

    void insert(T value);

    void insert(T value, Iterator _iter);

    void insertOrdered(T value);

    void clear();

    bool isEmpty() { return _size == 0; };
};

#endif //LINKED_LIST_LIST_H
