#include <utility>

//
// Created by Moustafa on 5/2/2019.
//

#ifndef DATASTRUCTURES_ASSIGNMENT4_20170288_CONTACTMANAGER_H
#define DATASTRUCTURES_ASSIGNMENT4_20170288_CONTACTMANAGER_H


#include "Contact.h"
#include "List.h"

class ContactManager {
private:
    List<Contact> contactList;

public:
    ContactManager() = default;

    ContactManager(Contact contact) { insert(contact); }

    void insert(Contact contact) { contactList.insertOrdered(contact); }

    void showContacts();
};


#endif //DATASTRUCTURES_ASSIGNMENT4_20170288_CONTACTMANAGER_H
