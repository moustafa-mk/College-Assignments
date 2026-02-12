//
// Created by Moustafa on 10-Apr-19.
//

#include "Course.h"

void changeFileState(std::string dataFile, bool state);

bool isEmpty(std::string dataFile);

void reconstructIndexes(const std::string &dataFile, std::vector<prIndex> &prVec,
                        std::map<std::string, std::vector<std::string>> &secIndexMap);

void readPrIndex(const std::string &prIndexFile, std::vector<prIndex> &prVec);

void readSecIndex(const std::string &secIndexFile, const std::string &invListFile,
                  std::map<std::string, std::vector<std::string>> &secIndexMap);

void readIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::string &secIndexFile,
                 const std::string &invListFile,
                 std::vector<prIndex> &prVec, std::map<std::string, std::vector<std::string>> &secIndexMap);

void Course::AddCourse(const std::string &dataFile, std::vector<prIndex> &prVec,
                       std::map<std::string, std::vector<std::string>> &secIndexMap) {
    changeFileState(dataFile, true);

    char *buffer = new char[1000];
    strcpy(buffer, this->ID);
    strcat(buffer, "|");
    strcat(buffer, this->name.c_str());
    strcat(buffer, "|");
    strcat(buffer, this->instructor.c_str());
    strcat(buffer, "|");
    strcat(buffer, std::to_string(static_cast<int>(this->weeks)).c_str());
    strcat(buffer, "|");

    std::fstream file(dataFile, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    int offset = static_cast<int>(file.tellg());
    file.close();

    AddInData(dataFile, buffer);
    AddInPrIndex(prVec, offset);
    AddInSecIndex(secIndexMap);

    delete[] buffer;
}

void changeFileState(std::string dataFile, bool state) {
    if (isEmpty(dataFile)) {
        std::fstream file(dataFile, std::ios::binary | std::ios::out);
        file << state;
        file.close();
    } else {
        std::fstream file(dataFile, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
        file.seekp(0, std::ios::beg);
        file << state;
        file.close();
    }
}

bool isEmpty(std::string dataFile) {
    std::fstream file(dataFile, std::ios::binary | std::ios::in);
    file.seekg(0, std::ios::end);
    return !(file.tellg() >= 0);
}

void Course::AddInData(const std::string &dataFile, char *buffer) {
    std::fstream file(dataFile, std::ios::binary | std::ios::app);

    auto len = static_cast<short>(strlen(buffer));
    file.write((char *) &len, sizeof len);
    file.write(buffer, len);

    file.close();
}

void Course::AddInPrIndex(std::vector<prIndex> &vec, int &offset) {
    prIndex ind{};
    strcpy(ind.ID, ID);
    ind.offset = offset;
    vec.push_back(ind);
    std::sort(vec.begin(), vec.end(), [](const prIndex &a, const prIndex &b) { return strcmp(a.ID, b.ID) < 0; });
}

void Course::AddInSecIndex(std::map<std::string, std::vector<std::string>> &secIndexMap) {
    secIndexMap[instructor].push_back(ID);
    sort(secIndexMap[instructor].begin(), secIndexMap[instructor].end());
}

void readIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::string &secIndexFile,
                 const std::string &invListFile,
                 std::vector<prIndex> &prVec, std::map<std::string, std::vector<std::string>> &secIndexMap) {
    if (isEmpty(dataFile))
        return;

    std::fstream file(dataFile, std::ios::binary | std::ios::in);
    bool flag;
    file >> flag;
    file.close();

    if (flag) {
        reconstructIndexes(dataFile, prVec, secIndexMap);
    } else {
        readPrIndex(prIndexFile, prVec);
        readSecIndex(secIndexFile, invListFile, secIndexMap);
    }
}

void readSecIndex(const std::string &secIndexFile, const std::string &invListFile,
                  std::map<std::string, std::vector<std::string>> &secIndexMap) {
    std::fstream secFile(secIndexFile, std::ios::in);
    std::fstream invFile(invListFile, std::ios::in);

    secFile.seekg(0, std::ios::end);
    invFile.seekg(0, std::ios::end);
    int secFileFinalPos = static_cast<int>(secFile.tellg());
    int invFileFinalPos = static_cast<int>(invFile.tellg());
    secFile.seekg(0, std::ios::beg);
    invFile.seekg(0, std::ios::beg);

    std::string instructor;
    int invOffset;
    std::string invOffset_str;
    while (!secFile.fail()) {
        getline(secFile, instructor, '|');
        getline(secFile, invOffset_str, '|');
        invOffset = std::stoi(invOffset_str);
        invFile.seekg(invOffset);

        while (!invFile.fail()) {
            std::string ID;
            int nextOffset;
            std::string nextOffset_str;

            getline(invFile, ID, '|');
            getline(invFile, nextOffset_str, '|');
            nextOffset = std::stoi(nextOffset_str);

            secIndexMap[instructor].push_back(ID);

            int invFileCurPos = static_cast<int>(invFile.tellg());
            if (nextOffset == -1 || invFile.fail() || invFileCurPos == invFileFinalPos)
                break;
        }
        int secFileCurPos = static_cast<int>(secFile.tellg());
        if (secFileCurPos == secFileFinalPos)
            break;
    }

    secFile.close();
    invFile.close();
}

void readPrIndex(const std::string &prIndexFile, std::vector<prIndex> &prVec) {
    std::fstream prFile(prIndexFile, std::ios::in);
    prFile.seekg(0, std::ios::end);
    int final = static_cast<int>(prFile.tellg());
    prFile.seekg(0, std::ios::beg);

    prIndex read{};
    while (!prFile.fail()) {
        prFile.getline(read.ID, 6, '|');
        std::string offset;
        getline(prFile, offset, '|');
        read.offset = std::stoi(offset);
        prVec.push_back(read);

        int pos = static_cast<int>(prFile.tellg());
        if (prFile.fail() || pos == final) break;
    }

    prFile.close();
}

void reconstructIndexes(const std::string &dataFile, std::vector<prIndex> &prVec,
                        std::map<std::string, std::vector<std::string>> &secIndexMap) {
    std::fstream data(dataFile, std::ios::binary | std::ios::in);
    data.seekg(0, std::ios::end);
    int final = static_cast<int>(data.tellg());
    data.seekg(1, std::ios::beg);

    Course temp;
    int offset;
    while (!data.fail()) {
        offset = static_cast<int>(data.tellg());
        if (offset == final)
            break;
        short len;
        data.read((char *) &len, sizeof len);
        char *buffer = new char[len];
        data.read(buffer, len);

        std::basic_istringstream<char> str_buf(buffer);

        str_buf.getline(temp.ID, 6, '|');
        getline(str_buf, temp.name, '|');
        getline(str_buf, temp.instructor, '|');
        std::string weeks;
        getline(str_buf, weeks, '|');
        temp.weeks = static_cast<short>(std::stoi(weeks));


        delete[] buffer;

        if (temp.ID[0] != '*') {
            temp.AddInPrIndex(prVec, offset);
            temp.AddInSecIndex(secIndexMap);
        }
        if (data.fail())
            break;
    }
    data.close();
    changeFileState(dataFile, false);
}

std::ostream &operator<<(std::ostream &os, const Course &course) {
    os << "ID: " << course.ID << " Name: " << course.name << " Instructor: " << course.instructor << " Weeks: "
       << course.weeks;
    return os;
}

std::istream &operator>>(std::istream &is, Course &course) {
    std::cout << "Enter ID: ";
    is.ignore();
    is.getline(course.ID, 6);
    std::cout << "Enter Name: ";
    getline(is, course.name);
    std::cout << "Enter Instructor Name: ";
    getline(is, course.instructor);
    std::cout << "Enter Number of Weeks: ";
    is >> course.weeks;
    return is;
}

void SavePrimaryIndex(const std::string &prIndexFile, const std::vector<prIndex> &prVec) {
    std::fstream file(prIndexFile, std::ios::out | std::ios::trunc);

    for (const prIndex &index : prVec) {
        file.write(index.ID, strlen(index.ID));
        file.write("|", 1);
        std::string offset_str = std::to_string(index.offset);
        file.write(offset_str.c_str(), offset_str.length());
        file.write("|", 1);
    }
    file.close();
}

void SaveSecondaryIndex(const std::string &secIndexFile, const std::string &invListFile,
                        const std::map<std::string, std::vector<std::string>> &secIndexMap) {
    std::fstream secIndex(secIndexFile, std::ios::out | std::ios::trunc);
    std::fstream invList(invListFile, std::ios::out | std::ios::trunc);

    int invListOffset;
    for (const auto &it : secIndexMap) {
        invListOffset = std::max(static_cast<int>(invList.tellp()), 0);
        std::string invListOffset_str = std::to_string(invListOffset);
        secIndex.write(it.first.c_str(), it.first.length());
        secIndex.write("|", 1);
        secIndex.write(invListOffset_str.c_str(), invListOffset_str.length());
        secIndex.write("|", 1);
        for (int i = 0; i < it.second.size(); i++) {
            const auto Vit = it.second[i];
            //std::string Vit_str = std::to_string(Vit);
            invList.write(Vit.c_str(), Vit.length());
            invList.write("|", 1);
            int nextOffset;
            if (i < it.second.size() - 1)
                nextOffset = invListOffset + Vit.length() + sizeof invListOffset + 2;
            else
                nextOffset = -1;
            std::string nextOffset_str = std::to_string(nextOffset);
            invList.write(nextOffset_str.c_str(), nextOffset_str.length());
            invList.write("|", 1);
            invListOffset = static_cast<int>(invList.tellp());
        }
    }
}

void DeleteByID(const std::string &dataFile, std::vector<prIndex> &prVec,
                std::map<std::string, std::vector<std::string>> &secIndexMap, char *ID) {
    auto it = std::lower_bound(prVec.begin(), prVec.end(), ID,
                               [](const prIndex &a, const char *ID) { return strcmp(a.ID, ID) < 0; });
    if (strcmp(it->ID, ID) != 0) {
        std::cout << "Record Not Found\n";
    } else {
        changeFileState(dataFile, true);
        std::fstream file(dataFile, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
        file.seekp(it->offset);

        Course temp;
        short len;
        file.read((char *) &len, sizeof len);
        file.getline(temp.ID, 6, '|');
        getline(file, temp.name, '|');
        getline(file, temp.instructor, '|');

        file.seekp(it->offset + sizeof len);
        file << '*';
        file.close();

        auto it2 = lower_bound(secIndexMap[temp.instructor].begin(), secIndexMap[temp.instructor].end(), temp.ID);
        secIndexMap[temp.instructor].erase(it2);
        if(secIndexMap[temp.instructor].empty()) {
            auto itx = secIndexMap.lower_bound(temp.instructor);
            secIndexMap.erase(itx);
        }
        prVec.erase(it);
    }
}

void DeleteByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                        std::map<std::string, std::vector<std::string>> &secIndexMap,
                        const std::string &instructor) {
    auto it = secIndexMap.lower_bound(instructor);

    if (it->first != instructor) {
        std::cout << "Record Not Found..\n";
    } else {
        changeFileState(dataFile, true);
        std::fstream file(dataFile, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
        for (const auto &ID : it->second) {
            DeleteByID(dataFile, prVec, secIndexMap, const_cast<char*>(ID.c_str()));
        }

        file.close();
        secIndexMap.erase(it);
    }
}

void PrintByID(const std::string &dataFile, const std::vector<prIndex> &prVec, char *ID) {
    auto it = std::lower_bound(prVec.begin(), prVec.end(), ID,
                               [](const prIndex &a, const char *ID) { return strcmp(a.ID, ID) < 0; });
    if (strcmp(it->ID, ID) != 0) {
        std::cout << "Record Not Found\n";
    } else {
        changeFileState(dataFile, true);
        std::fstream file(dataFile, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
        file.seekp(it->offset);

        Course temp;
        short len;
        file.read((char *) &len, sizeof len);
        char *buffer = new char[len];
        file.read(buffer, len);

        std::basic_istringstream<char> str_buf(buffer);

        str_buf.getline(temp.ID, 6, '|');
        getline(str_buf, temp.name, '|');
        getline(str_buf, temp.instructor, '|');
        std::string weeks;
        getline(str_buf, weeks, '|');
        temp.weeks = static_cast<short>(std::stoi(weeks));

        file.close();
        delete[] buffer;
        std::cout << temp << '\n';
    }
}

void PrintByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                       const std::map<std::string, std::vector<std::string>> &secIndexMap,
                       const std::string &instructor) {
    auto it = secIndexMap.lower_bound(instructor);

    if (it->first != instructor) {
        std::cout << "Record Not Found..\n";
    } else {
        std::fstream file(dataFile, std::ios::binary | std::ios::in);

        for (const auto &ID : secIndexMap.at(instructor)) {
            PrintByID(dataFile, prVec, const_cast<char*>(ID.c_str()));
        }

        file.close();
    }
}

void UpdateByID(const std::string &dataFile, std::vector<prIndex> &prVec,
                std::map<std::string, std::vector<std::string>> &secIndexMap, char *ID) {
    auto it = std::lower_bound(prVec.begin(), prVec.end(), ID);

    if (strcmp(it->ID, ID) != 0) {
        std::cout << "Record Not Found...\n";
    } else {
        DeleteByID(dataFile, prVec, secIndexMap, ID);

        Course temp;
        std::cin >> temp;

        temp.AddCourse(dataFile, prVec, secIndexMap);
    }
}

void UpdateByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                        std::map<std::string, std::vector<std::string>> &secIndexMap, const std::string &instructor) {
    auto it = secIndexMap.lower_bound(instructor);

    if (it->first != instructor) {
        std::cout << "Record Not Found...\n";
    } else {
        std::fstream file(dataFile, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
        for (const auto &ID : it->second) {
            std::cout << "Do you want to Update Record with ID: " << ID << "? y/n ";
            char choice;
            std::cin >> choice;

            if (choice != 'y') {
                continue;
            } else {
                file.close();
                DeleteByID(dataFile, prVec, secIndexMap, const_cast<char*>(ID.c_str()));
                Course temp;
                std::cin >> temp;
                temp.AddCourse(dataFile, prVec, secIndexMap);
                file.open(dataFile, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
            }
        }
        file.close();
    }
}

void SaveIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::vector<prIndex> &prVec,
                 const std::string &secIndexFile,
                 const std::string &invListFile, const std::map<std::string, std::vector<std::string>> &secIndexMap) {
    SavePrimaryIndex(prIndexFile, prVec);
    SaveSecondaryIndex(secIndexFile, invListFile, secIndexMap);
    changeFileState(dataFile, false);
}
