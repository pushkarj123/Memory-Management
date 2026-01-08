#include "allocator.h"
#include <limits>
// best fit strategy
std::list<Block>::iterator best_fit(std::list<Block>& blocks, size_t size) {
    auto best = blocks.end();
    size_t best_size = std::numeric_limits<size_t>::max();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->free && it->size >= size && it->size < best_size) {
            best = it;
            best_size = it->size;
        }
    }
    return best;
}
