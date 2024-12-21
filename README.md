# In-Memory Database Project

Welcome to the **In-Memory Database Project**, an implementation of a simple yet powerful in-memory database in C++. This project demonstrates various computer science concepts like Object-Oriented Programming (OOP), data structures, operator overloading, and regular expressions.

---

## Features

- **SET Operation**: Add or update key-value pairs in the database.
- **GET Operation**: Retrieve values by their corresponding keys.
- **DELETE Operation**: Remove key-value pairs from the database.
- **DISPLAY Operation**: View all the key-value pairs stored in the database.
- **FIND Operation**: Search for specific keys or values.

---

## Concepts Used

### 1. **Object-Oriented Programming (OOP)**
   - Encapsulation: The database and query engine functionalities are encapsulated within their respective classes (`Database` and `QueryEngine`).
   - Abstraction: Users interact with the database via simple commands executed by the `QueryEngine`.
   - Inheritance and Polymorphism: Extensible structure for future enhancements, such as adding more operations or derived classes.

### 2. **Data Structures**
   - **HashMap (std::unordered_map)**: Efficient storage and retrieval of key-value pairs.
   - **String Manipulation**: To parse and process queries using C++ string utilities.

### 3. **Regular Expressions (Regex)**
   - Used for parsing and validating user queries in the `QueryEngine`.
   - Ensures robustness in handling various input formats.

### 4. **Operator Overloading**
   - Custom behavior for certain operators (e.g., assignment or comparison) can be implemented for database objects if needed.

---

## Prerequisites

Make sure you have the following installed:
- **GCC** (GNU Compiler Collection) with C++17 support
- **Make** build automation tool

---

## Build and Run Instructions

### Step 1: Clone the Repository
```
git clone <repository-url>
cd in-memory-database
```

### Step 2: Build the Project
Use the provided `Makefile` to compile the project:
```
make
```

### Step 3: Run the Executable
After successful compilation, execute the program:
```
make run
```

### Step 4: Clean Up
To remove compiled files, use:
```
make clean
```

---

## Sample Usage

1. **Add Key-Value Pairs**:
   ```
   SET name John
   SET age 30
   SET city "New York"
   ```
2. **Display Database Contents**:
   ```
   DISPLAY
   ```
3. **Retrieve Values**:
   ```
   GET name
   GET city
   ```
4. **Delete Key-Value Pairs**:
   ```
   DELETE age
   ```
5. **Find Specific Keys or Values**:
   ```
   FIND name
   FIND "New York"
   ```

---

## Future Enhancements
- Add support for complex data types (e.g., arrays or nested objects).
- Implement persistence to allow saving and loading database contents from a file.
- Introduce multi-threading for handling concurrent queries.

