#include <iostream>
#include "../include/memory_manager.h"

using namespace std;

int main() {
    MemoryManager mm;
    string cmd;

    while (true) {
        cout << "> ";
        cin >> cmd;

        if (cmd == "init") {
            size_t size;
            cin >> size;
            mm.init(size);
        }
        else if (cmd == "set") {
            string type;
            cin >> type;
            mm.setAllocator(type);
        }
        else if (cmd == "malloc") {
            size_t size;
            cin >> size;
            mm.mallocBlock(size);
        }
        else if (cmd == "free") {
            int id;
            cin >> id;
            mm.freeBlock(id);
        }
        else if (cmd == "enable_buddy") {
            mm.enableBuddy();
        }
        else if (cmd == "buddy_malloc") {
            size_t size;
            cin >> size;
            mm.buddyMalloc(size);
        }
        else if (cmd == "buddy_free") {
            size_t addr, size;
            cin >> addr >> size;
            mm.buddyFree(addr, size);
        }
        else if (cmd == "dump") {
            mm.dump();
        }
        else if (cmd == "dump_buddy") {
            mm.dumpBuddy();
        }
        else if (cmd == "init_cache") {
            mm.initCache();
        }
        else if (cmd == "access") {
            size_t addr;
            cin >> addr;
            mm.accessMemory(addr);
        }
        else if (cmd == "cache_stats") {
            mm.cacheStats();
        }
        else if (cmd == "stats") {
            mm.stats();
        }
        else if (cmd == "exit") {
            break;
        }
    }
    return 0;
}
