#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <random>

// Pull in the wrapper + B+ tree code
#include "bptree_wrapper.cpp"

using bench_clock = std::chrono::high_resolution_clock;

void worker(BPlusTreeWrapper& tree, int ops, int id) {
    std::mt19937 rng(id + 123);
    for (int i = 0; i < ops; i++) {
        int key = rng() % 100000;
        tree.Insert(key, key);
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: bpbench <threads> <ops_per_thread>\n";
        return 0;
    }

    int threads = std::stoi(argv[1]);
    int ops = std::stoi(argv[2]);

    BPlusTreeWrapper tree;

    auto start = bench_clock::now();

    std::vector<std::thread> pool;
    for (int i = 0; i < threads; i++) {
        pool.emplace_back(worker, std::ref(tree), ops, i);
    }

    for (auto &t : pool) t.join();

    auto end = bench_clock::now();

    double seconds = std::chrono::duration<double>(end - start).count();
    long long total_ops = 1LL * threads * ops;

    std::cout << "Threads: " << threads << "\n";
    std::cout << "Operations: " << total_ops << "\n";
    std::cout << "Elapsed: " << seconds << " sec\n";
    std::cout << "Throughput: " << (total_ops / seconds) << " ops/sec\n";

    return 0;
}
