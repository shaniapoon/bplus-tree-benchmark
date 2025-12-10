Parallel B+ Tree Benchmark (CS4441 Project)

This repository contains the B+ Tree benchmarking implementation developed as part of a group project for CSC / CS4441 (Database Systems).

The objective of this component is to evaluate the performance and scalability of a traditional B+ Tree under concurrent workloads and compare it against advanced index structures such as Bw-tree.

The B+ Tree implementation is based on an open-source reference design and is extended with a wrapper, benchmarking harness, and automated dataset collection.

Project Structure
Parallel-BplusTree/
├── btree.cpp, btree.h       # B+ tree implementation
├── utils.cpp, utils.h       # Tree helpers and utilities
├── bptree_wrapper.cpp      # Thread-safe wrapper using mutex locking
├── benchmark.cpp           # Multithreaded benchmark driver
├── run_bptree.sh           # Automation script for repeated benchmarks
├── bptree_results.csv      # Collected throughput data
└── README.md

Features Implemented

Thread-safe B+ Tree wrapper using mutex locking

Multithreaded benchmarking harness

Throughput measurement for concurrent workloads

Automated CSV dataset generation

Compatible result format for cross-database comparison

Reproducible performance experiments

Build Instructions (Windows / MSYS2)

Open MSYS2 MinGW64 terminal and navigate to the project directory:

cd /c/Users/sanmao/bplus-tree-benchmark/Parallel-BplusTree


Compile the benchmark:

g++ -std=c++17 -O3 benchmark.cpp btree.cpp utils.cpp -o bpbench -pthread -fpermissive

▶️ Running Benchmarks

To run a single configuration:

./bpbench <threads> <operations>


Example:

./bpbench 4 50000


This runs 4 threads with 50,000 operations per thread.

Automated Dataset Collection

To generate a full dataset for a workload:

./run_bptree.sh workloada.spec
./run_bptree.sh workloadb.spec
./run_bptree.sh workloadc.spec
./run_bptree.sh workloadd.spec


Each script run:

Executes thread counts: 1, 2, 4, 8, 16, 32

Runs each configuration 3 times

Appends results to:

bptree_results.csv


CSV format:

workload,db,threads,throughput
workloada.spec,bptree,4,2015342
...

Result Analysis

Output CSV files can be processed using the shared Python plotting script:

df_raw = pd.read_csv("bptree_results.csv")


Common plots:

Throughput vs Thread Count

Speedup vs Thread Count

Scalability comparison against Bw-tree

Key Observations

The B+ tree shows:

Very high single-thread performance

Significant lock contention beyond two threads

Limited scalability under multi-threaded workloads

Performance patterns consistent with coarse-grained locking systems

These results contrast strongly with Bw-tree, which demonstrates superior scaling due to latch-free architecture.

Notes

This B+ tree uses mutex-based locking.

No optimistic concurrency or latch coupling was implemented.

The benchmarking harness was written in C++ for portability

Tests were run on Windows using MSYS2 MinGW64 environment

📎 License

This repository is for academic use only.
