//
// Created by Moustafa on 5/2/2019.
//

#include <iostream>
#include "Contact.h"

void Contact::showNumbers() {
    std::cout << name << '\t';
    for(const auto &number : phoneNumbers) std::cout << number << ' '; std::cout << '\n';
}

bool operator<(const Contact &lhs, const Contact &rhs) {
    return lhs.name < rhs.name;
}

bool operator>(const Contact &lhs, const Contact &rhs) {
    return rhs < lhs;
}

bool operator<=(const Contact &lhs, const Contact &rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Contact &lhs, const Contact &rhs) {
    return !(lhs < rhs);
}
