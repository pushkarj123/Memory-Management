#include "allocator.h"
// worst fit strategy
std::list<Block>::iterator worst_fit(std::list<Block>& blocks, size_t size) {
    auto worst = blocks.end();
    size_t worst_size = 0;

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->free && it->size >= size && it->size > worst_size) {
            worst = it;
            worst_size = it->size;
        }
    }
    return worst;
}
