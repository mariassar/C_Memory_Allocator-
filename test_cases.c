#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "my_mem.h"
#include "test_cases.h"

/* function to test allocating entire memory pool */
void test_mem_init(unsigned char *global_memory, unsigned int global_mem_size) {
    mem_init(global_memory, global_mem_size); /*initialize the memory pool */
    
    mem_stats_struct stats;  /* Declare the stats variable to retrieve memory statistics */
    mem_get_stats(&stats);
    
    assert(stats.num_blocks_free == 1);                     /* One initial free block */
    assert(stats.num_blocks_used == 0);                     /* No blocks used */
    assert(stats.num_blocks_free == 1);                     /* One free block */
    assert(stats.smallest_block_free == global_mem_size - sizeof(block_header));  /* Entire pool is free */
    assert(stats.largest_block_free == global_mem_size - sizeof(block_header));   /* Entire pool is free */

     print_stats("after initializing memory pool");
}

/* function to test allocating more memory than available */
void test_allocate_more_than_available_memory(unsigned int global_mem_size) {
    /* try to allocate a memory block larger than the available memory */
    unsigned char *ptr6 = my_malloc(global_mem_size + 100);
    assert(ptr6 == NULL);
    print_stats("after allocation failure");

}

/* function to test allocating and freeing random-sized memory blocks */
void test_allocate_free_random_sizes() {
    /* seed the random number generator */
    srand(time(NULL));
    
    /* declare an array to store pointers to allocated memory blocks */
    unsigned char *ptr_array[3];
    /* declare an array to store sizes of memory blocks */
    unsigned int sizes[3];

    /* loop to allocate random-sized memory blocks */
    for (int i = 0; i < 3; i++) {
        /* generate a random size between 1 and 200 */
        sizes[i] = rand() % 200 + 1;
        /* allocate memory block and store the pointer */
        ptr_array[i] = my_malloc(sizes[i]);
        /* check if allocation was successful */
        assert(ptr_array[i] != NULL);
    }

    print_stats("after allocating random sizes");

    /* define a random order to free memory blocks */
    int free_order[] = {0, 2, 1};
    /* loop to free memory blocks in random order (it will be random, as each 
    block allocated is a random size between 1 and 200 */
    for (int i = 0; i < 3; i++) {
        my_free(ptr_array[free_order[i]]);
    }

    print_stats("after freeing random sizes");
}

