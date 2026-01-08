#include "allocator.h"

std::list<Block>::iterator first_fit(std::list<Block>& blocks, size_t size) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it)
        if (it->free && it->size >= size)
            return it;
    return blocks.end();
}
