#include <utility>

//
// Created by Moustafa on 5/2/2019.
//

#ifndef DATASTRUCTURES_ASSIGNMENT4_20170288_INDEXBUILDER_H
#define DATASTRUCTURES_ASSIGNMENT4_20170288_INDEXBUILDER_H


#include "BSTFCI.h"
#include <string>

class indexBuilder {
    BSTFCI<std::string> btree;

public:
    indexBuilder() = default;

    indexBuilder(std::string text);

    void insert(std::string text);

    void print();

    void print(BSTFCI<std::string>::iterator it);
};


#endif //DATASTRUCTURES_ASSIGNMENT4_20170288_INDEXBUILDER_H
