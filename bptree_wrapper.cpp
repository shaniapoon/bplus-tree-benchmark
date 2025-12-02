#include <iostream>
#include <vector>
#include <cstring>

// B+ Tree header (C-style)
extern "C" {
    #include "Parallel-BplusTree/btree.h"
}

class BPlusTreeWrapper {
private:
    node *root;

public:
    BPlusTreeWrapper() : root(NULL) {
        std::cout << "[Wrapper] B+ Tree initialized\n";
    }

    // INSERT: key + value
    int Insert(int key, int value) {
        root = insert(root, key, value);
        return 0;
    }

    // READ: single key lookup
    int Read(int key, int &result) {
        node *leaf = NULL;
        record *r = find(root, key, false, &leaf);
        if (r == NULL) return 1;
        result = r->value;
        return 0;
    }

    // UPDATE = delete + insert
    int Update(int key, int value) {
        root = remove(root, key);
        root = insert(root, key, value);
        return 0;
    }

    // DELETE
    int Delete(int key) {
        root = remove(root, key);
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
