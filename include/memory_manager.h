#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <list>
#include <string>
#include <unordered_map>

#include "../src/allocator/allocator.h"
#include "../src/allocator/buddy_allocator.h"
#include "../src/cache/cache.h"

class MemoryManager {
private:
    // Variable-size allocator
    std::list<Block> blocks;
    size_t total_memory;
    AllocatorType allocator;
    int next_id;
    size_t used_memory;

    //Buddy allocator 
    bool buddy_enabled;
    BuddyAllocator* buddy;
    std::unordered_map<size_t, size_t> buddy_map;
    size_t buddy_internal_frag;

    // Cache 
    Cache* l1;
    Cache* l2;

public:
    MemoryManager();

    // Linear allocators 
    void init(size_t size);
    void setAllocator(const std::string& type);
    void mallocBlock(size_t size);
    void freeBlock(int id);
    void dump();
    void stats();

    // Buddy 
    void enableBuddy();
    void buddyMalloc(size_t size);
    void buddyFree(size_t addr, size_t size);
    void dumpBuddy();

    // Cache 
    void initCache();
    void accessMemory(size_t addr);
    void cacheStats();
};

#endif
