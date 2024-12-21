#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
#include <regex>
#include <unordered_set>

class Database {
private:
    // Data stored in the database
    std::unordered_map<std::string, std::variant<int, float, bool, std::string>> data;

    // Indexes for faster searching
    std::unordered_map<std::string, std::unordered_set<std::string>> keyIndex;
    std::unordered_map<std::variant<int, float, bool, std::string>, std::unordered_set<std::string>> valueIndex;

public:
    Database() {}

    void createOrUpdate(const std::string& key, const std::variant<int, float, bool, std::string>& value);
    std::variant<int, float, bool, std::string> read(const std::string& key);
    void displayAll();
    void createIndexOnKeys();
    void createIndexOnValues();
    std::vector<std::string> searchByKey(const std::string& key);
    std::vector<std::string> searchByValue(const std::variant<int, float, bool, std::string>& value);
    std::vector<std::string> searchByRegex(const std::string& regex);
    void filter(const std::string& key, const std::variant<int, float, bool, std::string>& value);
    void sortByKey(bool ascending = true);
    void sortByValue(bool ascending = true);
};

#endif
