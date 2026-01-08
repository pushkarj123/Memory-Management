#include "cache.h"
#include <iostream>

using namespace std;

// initialize cache 
Cache::Cache(size_t csize, size_t bsize)
    : cache_size(csize), block_size(bsize),
      fifo_ptr(0), hits(0), misses(0) {
    num_lines = cache_size / block_size;   // Number of cache lines
    lines.resize(num_lines, {false, 0});   // Initialize cache lines
}

// Access memory address 
bool Cache::access(size_t address) {
    size_t tag = address / block_size;     // Compute tag

    // Check for cache hit
    for (auto &line : lines) {
        if (line.valid && line.tag == tag) {
            hits++;
            return true;
        }
    }

    // Cache miss: replace using FIFO
    misses++;
    lines[fifo_ptr] = {true, tag};
    fifo_ptr = (fifo_ptr + 1) % num_lines;
    return false;
}

// Display cache statistics 
void Cache::stats() const {
    cout << "Hits: " << hits << "\n";
    cout << "Misses: " << misses << "\n";
}
