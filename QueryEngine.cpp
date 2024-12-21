#include "QueryEngine.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

void QueryEngine::handleSet(const std::string& key, const std::string& value) {
    try {
        if (value == "true" || value == "false") {
            db.createOrUpdate(key, value == "true");
        } else if (value.find('.') != std::string::npos) {
            db.createOrUpdate(key, std::stof(value));
        } else if (std::all_of(value.begin(), value.end(), ::isdigit)) {
            db.createOrUpdate(key, std::stoi(value));
        } else {
            db.createOrUpdate(key, value);
        }
    } catch (const std::exception& e) {
        std::cout << "Error: Invalid data type for key '" << key << "' - " << e.what() << "\n";
    }
}

void QueryEngine::handleGet(const std::string& key) {
    try {
        auto value = db.read(key);
        std::cout << "Key: " << key << " | Value: " 
          << std::visit([](auto&& arg) -> std::string { 
              if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                  return arg;  // No conversion needed for string type
              } else {
                  return std::to_string(arg);  // Convert other types to string
              }
          }, value) 
          << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void QueryEngine::handleSearchKey(const std::string& key) {
    auto result = db.searchByKey(key);
    for (const auto& res : result) {
        std::cout << "Found key: " << res << "\n";
    }
}

void QueryEngine::handleSearchValue(const std::string& value) {
    // Conversion based on value type
    // (for simplicity, let's assume all values are strings here for this example)
    db.searchByValue(value);
}

void QueryEngine::handleFilter(const std::string& key, const std::string& value) {
    // Similar type handling logic
    db.filter(key, value);
}

void QueryEngine::handleSort(const std::string& criteria, bool ascending) {
    if (criteria == "key") {
        db.sortByKey(ascending);
    } else if (criteria == "value") {
        db.sortByValue(ascending);
    }
}

void QueryEngine::executeQuery(const std::string& query) {
    std::stringstream ss(query);
    std::string command;
    ss >> command;

    if (command == "SET") {
        std::string key, value;
        ss >> key >> value;
        handleSet(key, value);
    } else if (command == "GET") {
        std::string key;
        ss >> key;
        handleGet(key);
    } else if (command == "SEARCH_KEY") {
        std::string key;
        ss >> key;
        handleSearchKey(key);
    } else if (command == "SEARCH_VALUE") {
        std::string value;
        ss >> value;
        handleSearchValue(value);
    } else if (command == "FILTER") {
        std::string key, value;
        ss >> key >> value;
        handleFilter(key, value);
    } else if (command == "SORT") {
        std::string criteria;
        bool ascending;
        ss >> criteria >> ascending;
        handleSort(criteria, ascending);
    }
}
