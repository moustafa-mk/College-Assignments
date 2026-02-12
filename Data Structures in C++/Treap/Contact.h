#include <utility>

//
// Created by Moustafa on 5/2/2019.
//

#ifndef DATASTRUCTURES_ASSIGNMENT4_20170288_CONTACT_H
#define DATASTRUCTURES_ASSIGNMENT4_20170288_CONTACT_H

#include "List.h"

class Contact {
private:
    List<std::string> phoneNumbers;
    std::string name;

public:
    Contact() = default;

    Contact(std::string name, std::string number) { this->name = name, phoneNumbers.insertOrdered(std::move(number)); }

    void addNumber(std::string number) { phoneNumbers.insertOrdered(number); }

    void addNumber(int number) { phoneNumbers.insertOrdered(std::to_string(number)); }

    void showNumbers();

    void setName(std::string name) { this->name = name; }

    friend bool operator<(const Contact &lhs, const Contact &rhs);

    friend bool operator>(const Contact &lhs, const Contact &rhs);

    friend bool operator<=(const Contact &lhs, const Contact &rhs);

    friend bool operator>=(const Contact &lhs, const Contact &rhs);

};


#endif //DATASTRUCTURES_ASSIGNMENT4_20170288_CONTACT_H
