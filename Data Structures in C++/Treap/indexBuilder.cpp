#include <utility>
#include <iostream>

//
// Created by Moustafa on 5/2/2019.
//

#include "indexBuilder.h"

indexBuilder::indexBuilder(std::string text) {
    insert(std::move(text));
}

void indexBuilder::insert(std::string text) {
    for(auto it = text.begin(); it != text.end(); it++) {
        auto ch = *it;
        if (ch == '.' || ch == ',')
            text.erase(it);
    }

    std::string temp;
    int wrd_idx = 1;
    for (int idx = 0; idx < text.length(); idx++) {
        if(text[idx] == ' ' || text[idx] == '\n') {
            if(!temp.empty()) {
                btree.insert(temp).position->lines.push_back(wrd_idx);
                temp = "";
            }
            if(text[idx] == '\n')
                wrd_idx++;
        } else {
            temp += text[idx];
        }
    }

    if(!temp.empty()) {
        btree.insert(temp).position->lines.push_back(wrd_idx);
    }
}

void indexBuilder::print() {
    std::cout << "Word\tValue\n";
    print(btree.begin());
}

void indexBuilder::print(BSTFCI<std::string>::iterator it) {
    if(it.position->left != nullptr) print(BSTFCI<std::string>::iterator(it.position->left));
    std::cout << it.position->value << '\t';
    for(auto line : it.position->lines) std::cout << line << ' '; std::cout << '\n';
    if(it.position->right != nullptr) print(BSTFCI<std::string>::iterator(it.position->right));
}
