#include <iostream>
#include <iomanip>
#include <limits>
#include "../include/memory_manager.h"

using namespace std;

// Constructor 
MemoryManager::MemoryManager()
    : total_memory(0),
      allocator(AllocatorType::FIRST_FIT),
      next_id(1),
      used_memory(0),
      buddy_enabled(false),
      buddy(nullptr),
      buddy_internal_frag(0),
      l1(nullptr),
      l2(nullptr) {}

// Initialize physical memory 
void MemoryManager::init(size_t size) {
    blocks.clear();
    blocks.emplace_back(0, size);
    total_memory = size;
    used_memory = 0;
    next_id = 1;
    cout << "Memory initialized with size " << size << "\n";
}

// Set allocation strategy 
void MemoryManager::setAllocator(const string& type) {
    if (type == "first_fit") allocator = AllocatorType::FIRST_FIT;
    else if (type == "best_fit") allocator = AllocatorType::BEST_FIT;
    else if (type == "worst_fit") allocator = AllocatorType::WORST_FIT;
}

// Allocate memory using selected strategy 
void MemoryManager::mallocBlock(size_t size) {
    auto it = (allocator == AllocatorType::FIRST_FIT) ? first_fit(blocks, size) :
              (allocator == AllocatorType::BEST_FIT)  ? best_fit(blocks, size)  :
                                                        worst_fit(blocks, size);

    if (it == blocks.end()) {
        cout << "Allocation failed\n";
        return;
    }

    size_t remaining = it->size - size;
    if (remaining > 0)
        blocks.insert(next(it), Block(it->start + size, remaining));

    it->size = size;
    it->free = false;
    it->id = next_id++;
    used_memory += size;

    cout << "Allocated id=" << it->id << " at address " << it->start << "\n";
}

// Free allocated memory block 
void MemoryManager::freeBlock(int id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free && it->id == id) {
            it->free = true;
            used_memory -= it->size;

            auto nxt = next(it);
            if (nxt != blocks.end() && nxt->free) {
                it->size += nxt->size;
                blocks.erase(nxt);
            }
            if (it != blocks.begin()) {
                auto prv = prev(it);
                if (prv->free) {
                    prv->size += it->size;
                    blocks.erase(it);
                }
            }
            cout << "Block freed\n";
            return;
        }
    }
}

// Display fragmentation statistics 
void MemoryManager::stats() {
    size_t free_mem = total_memory - used_memory;
    size_t largest_free = 0;

    for (auto &b : blocks)
        if (b.free)
            largest_free = max(largest_free, b.size);

    double external =
        free_mem ? 1.0 - (double)largest_free / free_mem : 0.0;

    cout << "Internal fragmentation (FF/BF/WF): 0 bytes\n";
    cout << "External fragmentation: " << external * 100 << "%\n";
    cout << "Buddy internal fragmentation: "
         << buddy_internal_frag << " bytes\n";
}

// Display memory layout 
void MemoryManager::dump() {
    for (auto &b : blocks) {
        cout << "[" << b.start << " - "
             << b.start + b.size - 1 << "] "
             << (b.free ? "FREE" : "USED") << "\n";
    }
}

// Buddy allocator

// Enable buddy allocator 
void MemoryManager::enableBuddy() {
    buddy = new BuddyAllocator(total_memory);
    buddy_enabled = true;
    cout << "Buddy allocator enabled\n";
}

// Allocate using buddy system 
void MemoryManager::buddyMalloc(size_t size) {
    size_t addr = buddy->alloc(size);
    if (addr == numeric_limits<size_t>::max()) {
        cout << "Buddy allocation failed\n";
        return;
    }

    size_t order = 0;
    while ((1ULL << order) < size)
        order++;

    size_t block = 1ULL << order;
    buddy_internal_frag += block - size;
    buddy_map[addr] = size;

    cout << "Buddy allocated at address " << addr << "\n";
}

// Free buddy-allocated block 
void MemoryManager::buddyFree(size_t addr, size_t size) {
    if (buddy_map.count(addr)) {
        size_t req = buddy_map[addr];
        size_t order = 0;
        while ((1ULL << order) < req)
            order++;
        buddy_internal_frag -= (1ULL << order) - req;
        buddy_map.erase(addr);
    }
    buddy->free(addr, size);
}

// Display buddy free lists 
void MemoryManager::dumpBuddy() {
    buddy->dump();
}

// Cache

// Initialize L1 and L2 caches 
void MemoryManager::initCache() {
    l1 = new Cache(128, 16);
    l2 = new Cache(512, 32);
    cout << "L1 and L2 cache initialized\n";
}

// Access memory through cache hierarchy 
void MemoryManager::accessMemory(size_t addr) {
    if (!l1->access(addr))
        l2->access(addr);
}

// Display cache statistics 
void MemoryManager::cacheStats() {
    cout << "L1 Cache:\n";
    l1->stats();
    cout << "L2 Cache:\n";
    l2->stats();
}
