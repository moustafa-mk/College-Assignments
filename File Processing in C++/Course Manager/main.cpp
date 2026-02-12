#include <iostream>
#include <vector>
#include <map>
#include "Course.h"

void readIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::string &secIndexFile,
                 const std::string &invListFile,
                 std::vector<prIndex> &prVec, std::map<std::string, std::vector<std::string>> &secIndexMap);

void DeleteByID(const std::string &dataFile, std::vector<prIndex> &prVec,
                std::map<std::string, std::vector<std::string>> &secIndexMap, char ID[6]);

void DeleteByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                        std::map<std::string, std::vector<std::string>> &secIndexMap,
                        const std::string &instructor);

void PrintByID(const std::string &dataFile, const std::vector<prIndex> &prVec, char ID[6]);

void
PrintByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec, const std::map<std::string, std::vector<std::string>> &secIndexMap,
                  const std::string &instructor);

void UpdateByID(const std::string &dataFile, std::vector<prIndex> &prVec,
                std::map<std::string, std::vector<std::string>> &secIndexMap, char ID[6]);

void UpdateByInstructor(const std::string &dataFile, std::vector<prIndex> &prVec,
                        std::map<std::string, std::vector<std::string>> &secIndexMap,
                        const std::string &instructor);

void
SaveIndexes(const std::string &dataFile, const std::string &prIndexFile, const std::vector<prIndex> &prVec,
            const std::string &secIndexFile,
            const std::string &invListFile,
            const std::map<std::string, std::vector<std::string>> &secIndexMap);

int main() {
    std::vector<prIndex> prVec;
    std::map<std::string, std::vector<std::string>> secIndexMap;

    std::string dataFile, prIndexFile, secIndexFile, invListFile = "invList.txt";

    std::cout << "Enter Data File: ";
    std::cin >> dataFile;
    std::cout << "Enter Primary Index File: ";
    std::cin >> prIndexFile;
    std::cout << "Enter Secondary Index File: ";
    std::cin >> secIndexFile;
    system("cls");

    readIndexes(dataFile, prIndexFile, secIndexFile, invListFile, prVec, secIndexMap);

    while (true) {
        bool Exit = false;
        std::cout << "1) Add New Record\n"
                     "2) Delete Course (ID)\n"
                     "3) Delete Course (Instructor Name)\n"
                     "4) Print Course (ID)\n"
                     "5) Print Course (Instructor Name)\n"
                     "6) Update Course (ID)\n"
                     "7) Update Course (Instructor Name)\n"
                     "8) Exit\n";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            system("pause");
            system("cls");
            continue;
        }

        switch (choice) {
            case 1: {
                system("cls");
                Course temp;
                std::cin >> temp;
                temp.AddCourse(dataFile, prVec, secIndexMap);
                system("pause");
                system("cls");
                break;
            }
            case 2: {
                system("cls");
                std::cout << "Enter ID of Record to be Deleted: ";
                char ID[6];
                std::cin >> ID;
                DeleteByID(dataFile, prVec, secIndexMap, ID);
                system("pause");
                system("cls");
                break;
            }
            case 3: {
                system("cls");
                std::cout << "Enter Instructor Name of Record to be Deleted: ";
                std::string Instructor;
                std::cin.ignore();
                getline(std::cin, Instructor);
                DeleteByInstructor(dataFile, prVec, secIndexMap, Instructor);
                system("pause");
                system("cls");
                break;
            }
            case 4: {
                system("cls");
                std::cout << "Enter ID of Record to be Printed: ";
                char ID[6];
                std::cin >> ID;
                PrintByID(dataFile, prVec, ID);
                system("pause");
                system("cls");
                break;
            }
            case 5: {
                system("cls");
                std::cout << "Enter Instructor Name of Record to be Printed: ";
                std::string Instructor;
                std::cin.ignore();
                getline(std::cin, Instructor);
                PrintByInstructor(dataFile, prVec, secIndexMap, Instructor);
                system("pause");
                system("cls");
                break;
            }
            case 6: {
                system("cls");
                std::cout << "Enter ID of Record to be Updated: ";
                char ID[6];
                std::cin >> ID;
                UpdateByID(dataFile, prVec, secIndexMap, ID);
                system("pause");
                system("cls");
                break;
            }
            case 7: {
                system("cls");
                std::cout << "Enter Instructor Name of Record to be Updated: ";
                std::string Instructor;
                std::cin.ignore();
                getline(std::cin, Instructor);
                UpdateByInstructor(dataFile, prVec, secIndexMap, Instructor);
                system("pause");
                system("cls");
                break;
            }
            case 8: {
                system("pause");
                system("cls");
                SaveIndexes(dataFile, prIndexFile, prVec, secIndexFile, invListFile, secIndexMap);
                Exit = true;
                break;
            }
            default: {
                system("pause");
                system("cls");
                break;
            }
        }
        if (Exit)
            break;
    }
}