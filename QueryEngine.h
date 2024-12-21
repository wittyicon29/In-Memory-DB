#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include "Database.h"
#include <string>

class QueryEngine {
private:
    Database& db;  // Use reference to avoid copying

    // Helper functions to handle different types of queries
    void handleSet(const std::string& key, const std::string& value);
    void handleGet(const std::string& key);
    void handleSearchKey(const std::string& key);
    void handleSearchValue(const std::string& value);
    void handleFilter(const std::string& key, const std::string& value);
    void handleSort(const std::string& criteria, bool ascending);

public:
    // Constructor that takes a reference to a Database object
    QueryEngine(Database& database) : db(database) {}

    void executeQuery(const std::string& query);
};

#endif
