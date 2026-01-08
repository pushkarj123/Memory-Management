#include "buddy_allocator.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

BuddyAllocator::BuddyAllocator(size_t size, size_t min_block)
    : total_size(size) {
    min_order = log2(min_block);
    max_order = log2(size);
    free_lists[max_order].push_back(0);
}

size_t BuddyAllocator::getOrder(size_t size) {
    size_t order = min_order;
    while ((1ULL << order) < size)
        order++;
    return order;
}

size_t BuddyAllocator::getBuddy(size_t addr, size_t order) {
    return addr ^ (1ULL << order);
}

size_t BuddyAllocator::alloc(size_t size) {
    size_t order = getOrder(size);

    for (size_t o = order; o <= max_order; ++o) {
        if (!free_lists[o].empty()) {
            size_t addr = free_lists[o].front();
            free_lists[o].pop_front();

            while (o > order) {
                o--;
                size_t buddy = addr + (1ULL << o);
                free_lists[o].push_back(buddy);
            }
            return addr;
        }
    }
    return numeric_limits<size_t>::max();
}

void BuddyAllocator::free(size_t addr, size_t size) {
    size_t order = getOrder(size);

    while (order < max_order) {
        size_t buddy = getBuddy(addr, order);
        auto &list = free_lists[order];
        auto it = find(list.begin(), list.end(), buddy);

        if (it == list.end())
            break;

        list.erase(it);
        addr = min(addr, buddy);
        order++;
    }
    free_lists[order].push_back(addr);
}

void BuddyAllocator::dump() {
    for (auto &[order, list] : free_lists) {
        cout << "Order " << order << ": ";
        for (auto addr : list)
            cout << addr << " ";
        cout << "\n";
    }
}
