# C Memory Allocator
### Introduction

The purpose of this project is to implement a basic yet functional memory allocator in the C programming language. The standard C programming environment includes a memory allocator accessed via `malloc()` and `free()` functions.

### Implementation Details

The core allocator implementation is based on two main functions: `my_malloc()` for memory allocation and `my_free()` for memory deallocation. The allocator utilizes a linked list of memory block headers to efficiently organize memory space into parts that can be allocated and reused.

### Files

- `my_mem.c`: This file contains the main functionality of the program. The strategy for allocation within the file is "first fit," meaning    the first block of sufficient size that is available is taken in a sequential manner. If the available (free) block size (within the 
   global memory pool) is greater than or equal to the required size, then it is allocated.
- `my_mem.h`: This header file defines the prototypes of the functions and structures used in my_mem.c. It's included by both my_mem.c and 
   test_cases.c.
- `test_cases.c`: Contains test cases to ensure the allocator's functionality and reliability.
- `test_cases.h`: This header file defines the prototypes of the test case functions used in test_cases.c. It's included by test_cases.c.
- `main.c`: This file includes the main function where the main program statistics as well as the functionality program statistics are 
   gathered and printed. The individual test functions are defined in test_cases.c. 

### Functionality
`mem_init()` Initializes the memory pool with the provided memory block and saves the pointer to the memory block and its size in global variables. This function also sets the initial block header to represent the entire memory pool as a single free block. The program breaks the bulk space `malloc()` into blocks with headers.

`my_malloc()` Functions equivalent to `malloc()`, but allocates memory from the initialized memory pool. This function searches for a free memory block of the required size in the memory pool (using a "first fit" strategy). If found, it allocates the block and returns a pointer to the memory region after the block header. If the block is larger than the requested size, it splits the block into two parts, one for the allocation and the other for the remaining free space.

`my_free()` Functions equivalent to free, but returns memory to the memory pool passed to `mem_init()`. This function takes a pointer to a memory region and extracts the block header pointer. It then marks the corresponding block as free and if adjacent blocks are also free, it merges them to create larger free blocks.

`mem_get_stats()` Collects statistics about the current memory allocation in the memory pool. This function traverses all memory blocks and calculates the number of free and used blocks. It also determines the sizes of the smallest and largest free/used blocks. Additionally, it updates the provided `mem_stats_ptr` structure with the collected statistics.

`print_stats()` Prints the statistics collected by mem_get_stats. This function calls `mem_get_stats()` to obtain the memory statistics and then prints the statistics with a provided prefix for identification.

### Usage

1. Clone the repository to your local machine.
2. Open a terminal/command prompt.
3. Navigate to the project directory.
4. Run the following command to build, run, and output the allocator:

   ```sh
   make 
5. Run the following command to view the contents of the output file:
   
   ``` sh
   cat mem.txt

### Performance
The Best Case performance for malloc and free is O(1) if the block is at the beginning of the list. Either the malloc function quickly finds the free block of the correct size or free deallocates the block at the beginning of the chain of blocks.

In the Worst Case, the functions have to go through the entire linked list of blocks, and the performance is O(n), where n is the number of free or used blocks in the chain.

The Average Case performance would depend on the requests for malloc and free from the main function, but in general, the average should be O(n/2).
