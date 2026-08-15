P1 – mymalloc

Author:
ak3053
Aadarsh Kumar
writeup
This project implements a custom memory allocator that has
malloc() and free() using a fixed-size heap as stated in project 
spec. It detects invalid frees, double frees, and memory leaks.
The heap is implemented as a linked list of chunks.
Each chunk has a header with size and allocation status (metadata) followed by payload(actual data).

Chunks are aligned to 8 bytes. Free blocks are merged on every
free() call.

Testing:
test_basic: basic allocation
test_align: alignment
test_split: block splitting
test_reuse: reusing freed memory
test_adj: merging adjacent blocks
test_invalid_free: error detection testing
test_inside: pointer detection inside of a block
test_doublefree: free called on already free space
test_leak: leak detection testing

All of these tests represent basic failure cases and essential functions for a memory allocator according to assignment spec. If mymalloc() is able to pass all of these tests, it is valid.

memgrind.c  stress tests over 50 workloads.
