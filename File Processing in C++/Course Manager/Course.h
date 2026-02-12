//
// Created by Moustafa on 10-Apr-19.
//

#ifndef FILEORG_ASSIGN3_20170288_COURSE_H
#define FILEORG_ASSIGN3_20170288_COURSE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include "prIndex.h"

class Course {
    char ID[6];
    std::string name;
    std::string instructor;
    short weeks;

public:
    void AddCourse(const std::string &dataFile, std::vector<prIndex> &prVec,
                   std::map<std::string, std::vector<std::string>> &secIndexMap);

    friend void DeleteByID(const std::string &dataFile, std::vector<prIndex> &prVec,
                           std::map<std::string, std::vector<std::string>> &secIndexMap, char ID[6]);

    friend void DeleteByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                                   std::map<std::string, std::vector<std::string>> &secIndexMap,
                                   const std::string &instructor);

    friend void PrintByID(const std::string &dataFile, const std::vector<prIndex> &prVec, char ID[6]);

    friend void
    PrintByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec, const std::map<std::string, std::vector<std::string>> &secIndexMap,
                      const std::string &instructor);

    friend void UpdateByID(const std::string &dataFile, std::vector<prIndex> &prVec,
                           std::map<std::string, std::vector<std::string>> &secIndexMap, char ID[6]);

    friend void UpdateByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                                   std::map<std::string, std::vector<std::string>> &secIndexMap,
                                   const std::string &instructor);

    friend void
    SaveIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::vector<prIndex> &prVec,
                const std::string &secIndexFile,
                const std::string &invListFile,
                const std::map<std::string, std::vector<std::string>> &secIndexMap);

    friend void SavePrimaryIndex(const std::string &prIndexFile, const std::vector<prIndex> &prVec);

    friend void SaveSecondaryIndex(const std::string &secIndexFile, const std::string &invListFile,
                                   const std::map<std::string, std::vector<std::string>> &secIndexMap);

    friend void changeFileState(std::string dataFile, bool state);

    friend bool isEmpty(std::string dataFile);

    friend void
    readIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::string &secIndexFile,
                const std::string &invListFile, std::vector<prIndex> &prVec,
                std::map<std::string, std::vector<std::string>> &secIndexMap);

    friend std::ostream &operator<<(std::ostream &os, const Course &course);

    friend std::istream &operator>>(std::istream &is, Course &course);

    friend void reconstructIndexes(const std::string &dataFile, std::vector<prIndex> &prVec,
                                   std::map<std::string, std::vector<std::string>> &secIndexMap);

private:
    void AddInData(const std::string &dataFile, char *buffer);

    void AddInPrIndex(std::vector<prIndex> &vec, int &offset);

    void AddInSecIndex(std::map<std::string, std::vector<std::string>> &secIndexMap);
};


#endif //FILEORG_ASSIGN3_20170288_COURSE_H
