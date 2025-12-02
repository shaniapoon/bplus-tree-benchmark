#include <string>
#include <iostream>

// Include your B+ tree header
#include "Parallel-BplusTree/btree.h"

class BPlusTreeWrapper {
private:
    BTree tree;   // the actual B+ tree

public:
    BPlusTreeWrapper() {
        std::cout << "[Wrapper] B+ Tree initialized.\n";
    }

    // Insert operation
    int Insert(const std::string &key, const std::string &value) {
        tree.insert(key, value);
        return 0; // success
    }

    // Read operation
    int Read(const std::string &key, std::string &result) {
        bool found = tree.find(key, result);
        return found ? 0 : 1;   // 0 = success, 1 = not found
    }

    // Update = Delete + Insert
    int Update(const std::string &key, const std::string &value) {
        tree.remove(key);
        tree.insert(key, value);
        return 0;
    }

    // Scan = range query
    int Scan(const std::string &start_key, int count) {
        tree.range_query(start_key, count);
        return 0;
    }
};
