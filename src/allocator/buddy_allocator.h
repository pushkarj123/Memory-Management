#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include <map>
#include <list>
#include <cstddef>

class BuddyAllocator {
private:
    size_t total_size;
    size_t min_order;
    size_t max_order;
    std::map<size_t, std::list<size_t>> free_lists;

    size_t getOrder(size_t size);
    size_t getBuddy(size_t addr, size_t order);

public:
    BuddyAllocator(size_t size, size_t min_block = 32);

    size_t alloc(size_t size);
    void free(size_t addr, size_t size);
    void dump();
};

#endif
