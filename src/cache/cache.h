#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstddef>
// cache struct define
struct CacheLine {
    bool valid;
    size_t tag;
};

class Cache {
private:
    size_t cache_size;
    size_t block_size;
    size_t num_lines;
    size_t fifo_ptr;

    size_t hits;
    size_t misses;

    std::vector<CacheLine> lines;

public:
    Cache(size_t cache_size, size_t block_size);

    bool access(size_t address);
    void stats() const;
};

#endif
