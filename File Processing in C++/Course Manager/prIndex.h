//
// Created by Moustafa on 10-Apr-19.
//

#ifndef FILEORG_ASSIGN3_20170288_PRINDEX_H
#define FILEORG_ASSIGN3_20170288_PRINDEX_H

#include <cstring>

class prIndex {
public:
    char ID[6];
    int offset;

    bool operator<(const prIndex &another) { return strcmp(ID, another.ID) < 0; }
    bool operator<(const char ID[]) { return strcmp(this->ID, ID) < 0; }
};


#endif //FILEORG_ASSIGN3_20170288_PRINDEX_H
