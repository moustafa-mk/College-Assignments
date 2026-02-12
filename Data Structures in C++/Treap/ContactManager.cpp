//
// Created by Moustafa on 5/2/2019.
//

#include "ContactManager.h"

void ContactManager::showContacts() {
    for(auto contact : contactList)
        contact.showNumbers();
}
