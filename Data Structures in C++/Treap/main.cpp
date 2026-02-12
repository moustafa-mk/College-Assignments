#include <iostream>
#include <fstream>
#include "BSTFCI.h"
#include "indexBuilder.h"
#include "ContactManager.h"
#include "Treap.h"

using namespace std;

int main() {
    /*auto *btree = new BSTFCI<int>;
    btree->insert(5);
    btree->insert(3);
    btree->insert(7);
    btree->insert(2);
    btree->insert(4);
    btree->insert(9);
    btree->insert(1);
    btree->insert(8);
    btree->insert(10);
    auto *btree2 = new BSTFCI<int>;
    btree2->insert(1);
    btree2->insert(2);
    btree2->insert(3);
    btree2->insert(4);
    btree2->insert(5);
//    cout << isSubTree(btree, btree2);
//    btree->printRange(6, 6);
    btree2->inorder();
    auto it = btree2->begin();
    ++it, ++it;
    btree2->flip(it);
    btree2->inorder();*/

/*
    indexBuilder builder;
    builder.insert("I am for truth,\nno matter who tells it.\nI am for justice,\nno matter who it is for or against.\nMalcom X");
    builder.print();
*/

/*
    ContactManager manager;
    fstream contacts(R"(E:\FCI\Prog1\Assignments\DataStructures-Assignment4-20170288\all-contacts.in)", ios::in);
    if(contacts.fail()) {
        cout << "Error opening file.\n";
    } else {
        contacts.seekg(0, ios::end);
        auto pos = contacts.tellg();
        contacts.seekg(0, ios::beg);
        while(!contacts.fail()) {
            string name, number;
            getline(contacts, number, ' ');
            getline(contacts, name, '\n');
            Contact contact(name, number);
            cout << name << ' ' << number << '\n';
            manager.insert(contact);
//            cout << "in\n";
            if(contacts.fail() || pos == contacts.tellg()) break;
        }
    }
    manager.showContacts();
*/

    Treap<string, string> treap;
    fstream contacts(R"(E:\FCI\Prog1\Assignments\DataStructures-Assignment4-20170288\all-contacts.in)", ios::in);
    if(contacts.fail()) {
        cout << "Error opening file.\n";
    } else {
        contacts.seekg(0, ios::end);
        auto pos = contacts.tellg();
        contacts.seekg(0, ios::beg);
        while(!contacts.fail()) {
            string name, number;
            getline(contacts, number, ' ');
            getline(contacts, name, '\n');
            treap.insert(number, name);
//            cout << "in\n";
            if(contacts.fail() || pos == contacts.tellg()) break;
        }
    }

    string find_str = "01246267569";
    cout    << treap.find(find_str) << '\n'
            << treap.find("123") << '\n';
}