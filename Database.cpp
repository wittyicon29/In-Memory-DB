    #include "Database.h"
    #include <algorithm>
    #include <functional>

    // Create or update data in the database
    void Database::createOrUpdate(const std::string& key, const std::variant<int, float, bool, std::string>& value) {
        data[key] = value;

        // Update the key index
        keyIndex[key].insert(key);

        // Update the value index
        valueIndex[value].insert(key);
    }

    // Read a specific value from the database
    std::variant<int, float, bool, std::string> Database::read(const std::string& key) {
        if (data.find(key) != data.end()) {
            return data[key];
        } else {
            throw std::runtime_error("Key not found");
        }
    }

    // Display all data in the database
    void Database::displayAll() {
        for (const auto& pair : data) {
            std::cout << "Key: " << pair.first << " | Value: ";
            if (std::holds_alternative<int>(pair.second)) {
                std::cout << std::get<int>(pair.second);
            } else if (std::holds_alternative<float>(pair.second)) {
                std::cout << std::get<float>(pair.second);
            } else if (std::holds_alternative<bool>(pair.second)) {
                std::cout << std::get<bool>(pair.second);
            } else if (std::holds_alternative<std::string>(pair.second)) {
                std::cout << std::get<std::string>(pair.second);
            }
            std::cout << std::endl;
        }
    }

    // Create an index on keys for fast lookup
    void Database::createIndexOnKeys() {
        for (const auto& pair : data) {
            keyIndex[pair.first].insert(pair.first);
        }
    }

    // Create an index on values for fast lookup
    void Database::createIndexOnValues() {
        for (const auto& pair : data) {
            valueIndex[pair.second].insert(pair.first);
        }
    }

    // Search by key
    std::vector<std::string> Database::searchByKey(const std::string& key) {
        std::vector<std::string> result;
        if (keyIndex.find(key) != keyIndex.end()) {
            result.push_back(key);
        }
        return result;
    }

    // Search by value
    std::vector<std::string> Database::searchByValue(const std::variant<int, float, bool, std::string>& value) {
        std::vector<std::string> result;
        if (valueIndex.find(value) != valueIndex.end()) {
            result.insert(result.end(), valueIndex[value].begin(), valueIndex[value].end());
        }
        return result;
    }

    // Search by regex
    std::vector<std::string> Database::searchByRegex(const std::string& regex) {
        std::vector<std::string> result;
        std::regex re(regex);
        for (const auto& pair : data) {
            if (std::regex_match(pair.first, re)) {
                result.push_back(pair.first);
            }
        }
        return result;
    }

    // Filter based on a key-value pair
    void Database::filter(const std::string& key, const std::variant<int, float, bool, std::string>& value) {
        if (data.find(key) != data.end() && data[key] == value) {
            std::cout << key << ": ";
            if (std::holds_alternative<int>(value)) {
                std::cout << std::get<int>(value);
            } else if (std::holds_alternative<float>(value)) {
                std::cout << std::get<float>(value);
            } else if (std::holds_alternative<bool>(value)) {
                std::cout << std::get<bool>(value);
            } else if (std::holds_alternative<std::string>(value)) {
                std::cout << std::get<std::string>(value);
            }
            std::cout << std::endl;
        }
    }

    void Database::sortByKey(bool ascending) {
        // Use a vector of pairs to sort the key-value pairs
        std::vector<std::pair<std::string, std::variant<int, float, bool, std::string>>> sortedData(data.begin(), data.end());

        if (ascending) {
            // Sort in ascending order by key
            std::sort(sortedData.begin(), sortedData.end(),
                    [](const auto& a, const auto& b) {
                        return a.first < b.first; // Compare by keys
                    });
        } else {
            // Sort in descending order by key
            std::sort(sortedData.begin(), sortedData.end(),
                    [](const auto& a, const auto& b) {
                        return a.first > b.first; // Compare by keys
                    });
        }

        // Rebuild the data map from the sorted vector
        data.clear();
        for (const auto& pair : sortedData) {
            data[pair.first] = pair.second;
        }
    }

    // Sort by value
    void Database::sortByValue(bool ascending) {
        // Use a vector of pairs to sort the key-value pairs
        std::vector<std::pair<std::string, std::variant<int, float, bool, std::string>>> sortedData(data.begin(), data.end());

        // Sorting function for variant types
        auto compareValues = [ascending](const auto& a, const auto& b) {
            // Use std::visit to handle different types in the variant
            return std::visit([ascending](auto&& val1, auto&& val2) {
                if constexpr (std::is_same_v<std::decay_t<decltype(val1)>, std::decay_t<decltype(val2)>>) {
                    // Compare values if types match
                    return ascending ? val1 < val2 : val1 > val2;
                } else {
                    // Handle different types (e.g., int vs string)
                    return false;
                }
            }, a.second, b.second);
        };

        // Sort the data based on values
        std::sort(sortedData.begin(), sortedData.end(), compareValues);

        // Rebuild the data map from the sorted vector
        data.clear();
        for (const auto& pair : sortedData) {
            data[pair.first] = pair.second;
        }
    }
