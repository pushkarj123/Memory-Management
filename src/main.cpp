#include <iostream>
#include "../include/memory_manager.h"

using namespace std;

int main() {
    MemoryManager mm;   // Memory manager instance
    string cmd;         // User command

    while (true) {
        cout << "> ";
        cin >> cmd;

        if (cmd == "init") {                 // Initialize memory
            size_t size;
            cin >> size;
            mm.init(size);
        }
        else if (cmd == "set") {             // Set allocation strategy
            string type;
            cin >> type;
            mm.setAllocator(type);
        }
        else if (cmd == "malloc") {          // Allocate memory
            size_t size;
            cin >> size;
            mm.mallocBlock(size);
        }
        else if (cmd == "free") {            // Free memory block
            int id;
            cin >> id;
            mm.freeBlock(id);
        }
        else if (cmd == "enable_buddy") {    // Enable buddy allocator
            mm.enableBuddy();
        }
        else if (cmd == "buddy_malloc") {    // Buddy allocation
            size_t size;
            cin >> size;
            mm.buddyMalloc(size);
        }
        else if (cmd == "buddy_free") {      // Buddy deallocation
            size_t addr, size;
            cin >> addr >> size;
            mm.buddyFree(addr, size);
        }
        else if (cmd == "dump") {             // Show memory layout
            mm.dump();
        }
        else if (cmd == "dump_buddy") {       // Show buddy free lists
            mm.dumpBuddy();
        }
        else if (cmd == "init_cache") {       // Initialize cache
            mm.initCache();
        }
        else if (cmd == "access") {           // Access memory address
            size_t addr;
            cin >> addr;
            mm.accessMemory(addr);
        }
        else if (cmd == "cache_stats") {      // Cache statistics
            mm.cacheStats();
        }
        else if (cmd == "stats") {             // Memory statistics
            mm.stats();
        }
        else if (cmd == "exit") {              // Exit simulator
            break;
        }
    }
    return 0;
}
