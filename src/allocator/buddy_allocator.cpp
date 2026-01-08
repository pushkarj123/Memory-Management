#include "buddy_allocator.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

// initialize buddy system 
BuddyAllocator::BuddyAllocator(size_t size, size_t min_block)
    : total_size(size) {
    min_order = log2(min_block);   // Minimum block size order
    max_order = log2(size);        // Maximum block size order
    free_lists[max_order].push_back(0);  // Entire memory initially free
}

// Determine required block order 
size_t BuddyAllocator::getOrder(size_t size) {
    size_t order = min_order;
    while ((1ULL << order) < size)
        order++;
    return order;
}

// Compute buddy address 
size_t BuddyAllocator::getBuddy(size_t addr, size_t order) {
    return addr ^ (1ULL << order);
}

// Allocate memory using buddy system 
size_t BuddyAllocator::alloc(size_t size) {
    size_t order = getOrder(size);

    for (size_t o = order; o <= max_order; ++o) {
        if (!free_lists[o].empty()) {
            size_t addr = free_lists[o].front();
            free_lists[o].pop_front();

            // Split blocks until desired order is reached
            while (o > order) {
                o--;
                size_t buddy = addr + (1ULL << o);
                free_lists[o].push_back(buddy);
            }
            return addr;
        }
    }
    return numeric_limits<size_t>::max();  // Allocation failed
}

// Free memory and merge buddies 
void BuddyAllocator::free(size_t addr, size_t size) {
    size_t order = getOrder(size);

    while (order < max_order) {
        size_t buddy = getBuddy(addr, order);
        auto &list = free_lists[order];
        auto it = find(list.begin(), list.end(), buddy);

        if (it == list.end())
            break;

        list.erase(it);                  // Remove buddy
        addr = min(addr, buddy);         // Merge blocks
        order++;
    }
    free_lists[order].push_back(addr);
}

// Display free lists 
void BuddyAllocator::dump() {
    for (auto &[order, list] : free_lists) {
        cout << "Order " << order << ": ";
        for (auto addr : list)
            cout << addr << " ";
        cout << "\n";
    }
}
