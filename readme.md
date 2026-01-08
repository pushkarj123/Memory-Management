# 2. Design Document

## 2.1 Memory Layout and Assumptions

The memory management simulator models a contiguous physical memory as a linear address space ranging from address 0 to N−1, where N represents the total memory size specified during initialization. Memory is managed as a sequence of variable-sized blocks, each identified by a starting address, size, and allocation status.

Each allocated block is assigned a unique identifier to support deallocation. Free blocks are maintained explicitly and reused by allocation strategies.

### Assumptions
- The system operates in a single-process, single-threaded environment.
- All memory allocation and deallocation requests are handled sequentially.
- Addresses are byte-addressable.
- No hardware memory management unit (MMU) or page tables are involved.
- Memory protection, access permissions, and concurrency are not modeled.

These assumptions simplify the design while allowing clear observation of allocation behavior and fragmentation.

---

## 2.2 Allocation Strategy Implementations

The simulator implements three classical variable-size memory allocation strategies.

### First Fit
The first fit strategy scans the list of memory blocks from the beginning and allocates the first free block that is large enough to satisfy the request. This approach has low allocation overhead but can lead to fragmentation near lower memory addresses.

### Best Fit
The best fit strategy searches all available free blocks and selects the smallest block that can accommodate the requested size. While this reduces wasted space within free blocks, it increases allocation time and can create small unusable fragments.

### Worst Fit
The worst fit strategy allocates memory from the largest available free block. This approach attempts to leave medium-sized blocks for future requests but often results in inefficient memory utilization.

### Block Splitting and Coalescing
When a free block is larger than the requested size, it is split into an allocated block and a remaining free block. When memory is freed, adjacent free blocks are merged to reduce external fragmentation.

### Fragmentation Handling
- Internal fragmentation is zero for these strategies because blocks are split exactly to the requested size.
- External fragmentation arises due to non-contiguous free blocks and is measured based on the ratio of the largest free block to total free memory.

---

## 2.3 Buddy System Design

To demonstrate fixed-size allocation, the simulator includes a buddy system allocator.

The buddy allocator manages memory in blocks whose sizes are powers of two. The total memory size is assumed to be a power of two, and free blocks are organized into order-based free lists.

### Allocation
For each request, the allocator determines the smallest power-of-two block that can satisfy the request. If a block of the required size is not available, larger blocks are recursively split until a suitable block is obtained.

### Deallocation
When a block is freed, its buddy is identified using address-based computation. If both the block and its buddy are free, they are merged. This merging process continues recursively, reducing external fragmentation.

### Fragmentation Characteristics
- Internal fragmentation exists due to rounding requested sizes up to the nearest power of two.
- External fragmentation is minimized through systematic merging of free buddies.

---

## 2.4 Cache Hierarchy and Replacement Policy

The simulator models a simplified two-level cache hierarchy consisting of an L1 cache and an L2 cache.

The L1 cache is smaller and faster, while the L2 cache is larger and slower. Both caches are fully associative and consist of cache lines containing a valid bit and a tag.

### Replacement Policy
A First-In-First-Out (FIFO) replacement policy is used at both cache levels. On a cache miss, the oldest cache line is evicted and replaced with the new block. FIFO is chosen for simplicity and to avoid the complexity of maintaining usage history.

Cache behavior is analyzed using hit and miss statistics rather than per-access output.

---

## 2.5 Address Translation Flow

The simulator uses a conceptual address translation model. Memory addresses issued by the user are treated as physical addresses. These addresses are first checked in the cache hierarchy, and on a cache miss, the access is serviced by the memory allocator.

Although no virtual memory or paging is implemented, this abstraction mirrors the logical flow of address resolution in real systems and allows future extension.

---

## 2.6 Limitations and Simplifications

To keep the simulator focused and manageable, the following limitations are imposed:

- No virtual memory or paging support.
- No translation lookaside buffer (TLB).
- No multi-process or multi-threaded execution.
- No memory protection or access control.
- Fully associative cache model.
- FIFO replacement policy only.
- Single contiguous physical memory region.

These simplifications allow the simulator to clearly demonstrate memory allocation strategies, fragmentation behavior, and cache hierarchy effects.

---

## 2.7 Summary

The design of the memory management simulator balances conceptual accuracy with implementation simplicity. By integrating variable-size allocation strategies, a buddy system allocator, and a cache hierarchy, the simulator effectively demonstrates fundamental operating system memory management concepts and their trade-offs.

The modular structure of the design enables easy extension to advanced features such as paging, virtual memory, and alternative cache replacement policies.

---
