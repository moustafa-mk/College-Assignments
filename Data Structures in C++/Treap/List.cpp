//
// Created by Moustafa on 13-Apr-19.
//

#include "List.h"
#include "Contact.h"

template<typename T>
List<T>::Iterator::Iterator() {
    position = nullptr;
}

template<typename T>
List<T>::Iterator::Iterator(List::Node *_node) {
    position = _node;
}

template<typename T>
void List<T>::Iterator::operator++(int) {
    ++(*this);
}

template<typename T>
void List<T>::Iterator::operator++() {
    if (position != nullptr)
        position = position->next;
}

template<typename T>
void List<T>::Iterator::operator--() {
    if (position != nullptr)
        position = position->prev;
}

template<typename T>
T &List<T>::Iterator::operator*() {
    return position->data;
}

template<typename T>
bool List<T>::Iterator::operator==(const List::Iterator &_iter) {
    return position == _iter.position;
}

template<typename T>
bool List<T>::Iterator::operator!=(const List::Iterator &_iter) {
    return !(*this == _iter);
}

template<typename T>
List<T>::List() {
    dummy = new Node();
    _size = 0;
}

template<typename T>
List<T>::List(const List<T> &another) {
    Node *node = another.head;
    if(node != nullptr) {
        head = new Node;
        head->data = node->data;
        Node *curr = head;
        while(node != another.dummy) {
            node = node->next;
            if(node == another.dummy)
                break;
            curr->next = new Node;
            curr->next->prev = curr;
            curr = curr->next;
            curr->data = node->data;
        }
        tail = curr;
        dummy = new Node;
        tail->next = dummy;
        dummy->prev = tail;
        head->prev = dummy;
        dummy->next = head;
    }
}

template<typename T>
List<T>::List(T value, int initial_size) {
    dummy = new Node;
    _size = 0;

    for (int i = 0; i < initial_size; i++)
        insert(value);
}

template<typename T>
void List<T>::insert(T value) {
    Node *_node = new Node();
    _node->data = value;


    if (head == nullptr && tail == nullptr) {
        head = new Node();
        tail = new Node();
        head = tail = _node;
        _node->next = dummy;
        _node->prev = dummy;
        dummy->next = head;
        dummy->prev = tail;
    } else if (head == tail) {
        head->next = _node;
        tail = _node;
        _node->next = dummy;
        _node->prev = head;
        dummy->next = head;
        dummy->prev = tail;
    } else {
        tail->next = _node;
        _node->next = dummy;
        _node->prev = tail;
        tail = _node;
        dummy->prev = tail;
    }
    _size++;
}

template<typename T>
void List<T>::insert(T value, List::Iterator _iter) {
    Node *_node = new Node();
    _node->data = value;

    if (head == nullptr && tail == nullptr) {
        //head = new Node();
        tail = new Node();
        head = tail = dummy;
        head->next = head->prev = dummy;
        //tail->next = tail->prev = dummy;
        //dummy->next = head;
        //dummy->prev = tail;
    }

    if (_iter == begin()) {
        _node->next = head;
        _node->prev = dummy;
        head->prev = _node;
        head = _node;
//        head->next->prev = _node;
        dummy->next = head;
        if (tail == dummy)
            tail = _node, dummy->prev = tail;
    } else if (_iter == end()) {
        _node->next = dummy;
        _node->prev = tail;
        tail->next = _node;
        tail = _node;
        dummy->prev = tail;
        if (head == dummy)
            head = _node, dummy->next = head;
    } else {
        _node->next = _iter.position;
        _node->prev = _iter.position->prev;
        _iter.position->prev->next = _node;
        _iter.position->prev = _node;
    }
    _size++;
}

template<typename T>
void List<T>::insertOrdered(T value) {
    if(!size()) {
        insert(value, begin());
    } else {
        auto it = begin();
        while(it != end()) {
            if(*it <= value) {
                ++it;
            } else {
                insert(value, it);
                return;
            }
        }
        insert(value, end());
    }
}

template<typename T>
List<T>::~List() {
    if(head != nullptr) {
        auto node = head;
        while (node != dummy && node != nullptr) {
            auto node2 = node->next;
            if (node2 == nullptr) {
                delete node;
                break;
            }
            delete node;
            node = node2;
        }
        delete dummy;
        head = nullptr;
    }
}

template<typename T>
typename List<T>::Iterator List<T>::erase(List::Iterator _iter) {
    if(_iter == begin())
        head = _iter.position->next;
    else if(_iter == end())
        --_iter, tail = _iter.position->prev;

    _iter.position->prev->next = _iter.position->next;
    _iter.position->next->prev = _iter.position->prev;

    Iterator it = Iterator(_iter.position->next);
    delete _iter.position;
    return it;
}

template<typename T>
List<T> &List<T>::operator=(List list) {
    clear();
    for (const auto &it : list) {
        insert(it);
    }

    tail->next = dummy;
    dummy->prev = tail;
    head->prev = dummy;
    dummy->next = head;
    return *this;
}

template<typename T>
void List<T>::clear() {
    for (Iterator it = begin(); it != end();) {
        it = Iterator(it.position->next);
        delete it.position->prev;
    }
    _size = 0;
}

template
class List<int>;

template
class List<std::string>;

template class List<Contact>;
