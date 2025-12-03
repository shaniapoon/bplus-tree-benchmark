#include <iostream>
#include <vector>
#include <cstring>

#include "btree.h"


class BPlusTreeWrapper {
private:
    node *root;

public:
    BPlusTreeWrapper() : root(NULL) {
        std::cout << "[Wrapper] B+ Tree initialized\n";
    }

    // INSERT
    int Insert(int key, int value) {
        root = insert(root, key, value);
        return 0;
    }

    // READ
    int Read(int key, int &result) {
        node *leaf = NULL;
        record *r = find(root, key, false, &leaf);
        if (r == NULL) return 1;
        result = r->value;
        return 0;
    }

    // UPDATE = delete + insert
    int Update(int key, int value) {
        root = bptree_remove(root, key);
        root = insert(root, key, value);
        return 0;
    }

    // DELETE
    int Delete(int key) {
        root = bptree_remove(root, key);
        return 0;
    }

    // RANGE SCAN
    int Scan(int start_key, int end_key, std::vector<int> &results) {
        const int MAX = 10000;
        int keys[MAX];
        void *pointers[MAX];

        int found = find_range(root, start_key, end_key, false, keys, pointers);
        for (int i = 0; i < found; i++) {
            record *r = (record *) pointers[i];
            results.push_back(r->value);
        }
        return 0;
    }
};

// ------------------
// Tiny test harness
// ------------------
int main() {
    BPlusTreeWrapper db;

    db.Insert(10, 1000);
    db.Insert(20, 2000);
    db.Insert(30, 3000);

    int value;
    if (db.Read(20, value) == 0) {
        std::cout << "Read(20) = " << value << std::endl;
    }

    db.Update(20, 9999);
    db.Read(20, value);
    std::cout << "Updated(20) = " << value << std::endl;

    std::vector<int> results;
    db.Scan(10, 30, results);

    std::cout << "Range Scan (10–30): ";
    for (auto &v : results) std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}




















































