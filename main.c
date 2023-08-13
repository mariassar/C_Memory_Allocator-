#include <stdio.h>                                             
#include <stdlib.h>                                             
#include <assert.h>                                             
#include "my_mem.h"                                           
#include "test_cases.h"                                       

int main() { 
    unsigned int global_mem_size = 1024 * 1024;                 // Set the size of the global memory pool in bytes (1MB)
    unsigned char *global_memory = malloc(global_mem_size);     // Allocate memory for the global memory pool

    if (!global_memory) {
        perror("Memory allocation error");                      // Print an error message if memory allocation fails
        exit(1);                                                // Exit the program with an error status
    }

    mem_init(global_memory, global_mem_size);                   // Initialize the memory manager with the global memory pool

    printf("Main Program Statistics:\n");   
    // Initial Statistics
    mem_stats_struct initial_stats;                             // Declare a structure to hold initial memory statistics
    mem_get_stats(&initial_stats);                              // Get the initial memory statistics
    print_stats("After initialization");          

    // Allocate and Free Blocks
    {
        unsigned char *ptr_array[10];                           // Declare an array to hold pointers to allocated memory
        unsigned int sizes[] = {50, 20, 20, 20, 50, 0};         // Array of sizes for memory allocation

        // Loop through the sizes array and allocate memory, print statistics after each allocation
        for (int i = 0; sizes[i] != 0; i++) {
            char buf[1024];                                     // Buffer for formatting print message
            ptr_array[i] = my_malloc(sizes[i]);                 // Allocate memory using the memory manager
            sprintf(buf, "After allocation %d size %d", i, sizes[i]);  
            print_stats(buf);                                   // Print memory statistics with the formatted message
        }

        // Free memory allocated at each index in the ptr_array and print memory statistics after freeing memory
        my_free(ptr_array[1]);                                  
        print_stats("After free #1");  

        my_free(ptr_array[3]);   
        print_stats("After free #3");   

        my_free(ptr_array[2]);   
        print_stats("After free #2");  

        my_free(ptr_array[0]);   
        print_stats("After free #0");   

        my_free(ptr_array[4]);  
        print_stats("After free #4");  
    
    }

    printf("Program Functionality Tests Statistics:\n"); 
    test_allocate_entire_memory(global_mem_size);
    test_allocate_more_than_available_memory(global_mem_size);
    test_free_null_pointer(global_mem_size);
    test_allocate_free_random_sizes(global_mem_size);  
    
    free(global_memory);

    return 0;   
}