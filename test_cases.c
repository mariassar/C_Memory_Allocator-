#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "my_mem.h"
#include "test_cases.h"

// Function to test allocating entire memory pool
void test_allocate_entire_memory() {
    // Declare an array to store pointers to allocated memory blocks
    unsigned char *ptr_array[10];
    // Define sizes of memory blocks to allocate
    unsigned int sizes[] = {100, 200, 300, 400, 500, 0};

    // Loop through the sizes array and allocate memory blocks
    for (int i = 0; sizes[i] != 0; i++) {
        // Allocate memory block and store the pointer
        ptr_array[i] = my_malloc(sizes[i]);
        assert(ptr_array[i] != NULL);  // Check allocation success
    }

    print_stats("After allocating entire memory pool");
}

// Function to test allocating more memory than available
void test_allocate_more_than_available_memory(unsigned int global_mem_size) {
     // Try to allocate a memory block larger than the available memory
    unsigned char *ptr6 = my_malloc(global_mem_size + 100);
    assert(ptr6 == NULL);  // Allocation should fail
    print_stats("After allocation failure");
}

// Function to test freeing a NULL pointer
void test_free_null_pointer() {
    // Free a NULL pointer (should not cause any issues)
    my_free(NULL); 
    print_stats("After freeing NULL pointer");
}

// Function to test allocating and freeing random-sized memory blocks
void test_allocate_free_random_sizes() {
    // Seed the random number generator
    srand(time(NULL));

    // Declare an array to store pointers to allocated memory blocks
    unsigned char *ptr_array[3];
    // Declare an array to store sizes of memory blocks
    unsigned int sizes[3];

    // Loop to allocate random-sized memory blocks
    for (int i = 0; i < 3; i++) {
        // Generate a random size between 1 and 200
        sizes[i] = rand() % 200 + 1;
        // Allocate memory block and store the pointer
        ptr_array[i] = my_malloc(sizes[i]);
        // Check if allocation was successful
        assert(ptr_array[i] != NULL);
    }

    print_stats("After allocating random sizes");

    // Define a random order to free memory blocks
    int free_order[] = {0, 2, 1};
    /* Loop to free memory blocks in random order (it will be random, as each 
    block allocated is a random size between 1 and 200*/
    for (int i = 0; i < 3; i++) {
        my_free(ptr_array[free_order[i]]);
    }

    print_stats("After freeing random sizes");
}





