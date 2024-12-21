#include "Database.h"
#include "QueryEngine.h"
#include <iostream>

int main() {
    Database db;  
    QueryEngine queryEngine(db);  

    // Test SET operation: Adding key-value pairs
    std::cout << "Testing SET operation:\n";
    queryEngine.executeQuery("SET name John");
    queryEngine.executeQuery("SET age 30");
    queryEngine.executeQuery("SET city New York");

    // Test DISPLAY operation: Show all entries after SET
    std::cout << "\nDatabase Contents After Update (DISPLAY):\n";
    queryEngine.executeQuery("DISPLAY");

    // Test GET operation: Retrieving specific values by key
    std::cout << "\nTesting GET operation:\n";
    queryEngine.executeQuery("GET name");    // Should output: John
    queryEngine.executeQuery("GET age");     // Should output: 30
    queryEngine.executeQuery("GET city");    // Should output: New York

    // Test DELETE operation: Removing a key-value pair
    std::cout << "\nTesting DELETE operation:\n";
    queryEngine.executeQuery("DELETE age");

    // Test DISPLAY operation after DELETE
    std::cout << "\nDatabase Contents After Deletion (DISPLAY):\n";
    queryEngine.executeQuery("DISPLAY");  // Should no longer show "age"

    // Test GET operation after DELETE
    std::cout << "\nTesting GET operation for deleted key (age):\n";
    queryEngine.executeQuery("GET age");  // Should indicate no such key exists

    // Test FIND operation: Finding specific keys or values
    std::cout << "\nTesting FIND operation:\n";
    queryEngine.executeQuery("FIND name");  // Should output: name -> John
    queryEngine.executeQuery("FIND New York");  // Should output: city -> New York

    // Test edge case: FIND for non-existent key or value
    std::cout << "\nTesting FIND operation for non-existent key:\n";
    queryEngine.executeQuery("FIND nonExistentKey");  // Should indicate not found

    // Test SET with duplicate key (should overwrite the value)
    std::cout << "\nTesting SET with duplicate key (name):\n";
    queryEngine.executeQuery("SET name Alice");
    queryEngine.executeQuery("GET name");  // Should output: Alice

    // Test SET operation with special characters or spaces
    std::cout << "\nTesting SET with special characters:\n";
    queryEngine.executeQuery("SET \"full name\" \"John Doe\"");
    queryEngine.executeQuery("GET \"full name\"");  // Should output: John Doe

    // Final DISPLAY of all contents
    std::cout << "\nFinal Database Contents (DISPLAY):\n";
    queryEngine.executeQuery("DISPLAY");

    return 0;
}
