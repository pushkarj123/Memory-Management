#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <list>
#include <cstddef>

struct Block {
    size_t start;
    size_t size;
    bool free;
    int id;

    Block(size_t s, size_t sz)
        : start(s), size(sz), free(true), id(-1) {}
};

enum class AllocatorType {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

std::list<Block>::iterator first_fit(std::list<Block>& blocks, size_t size);
std::list<Block>::iterator best_fit(std::list<Block>& blocks, size_t size);
std::list<Block>::iterator worst_fit(std::list<Block>& blocks, size_t size);

#endif
