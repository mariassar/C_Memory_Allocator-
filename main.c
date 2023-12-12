#include <stdio.h>                                             
#include <stdlib.h>                                             
#include <assert.h>                                             
#include "my_mem.h"                                           
#include "test_cases.h"                                       

int main() { 
    unsigned int global_mem_size = 1024 * 1024;                 /* set the size of the global memory pool in bytes (1MB) */
    unsigned char *global_memory = malloc(global_mem_size);     /* grabs memory from malloc */

    if (!global_memory) {
        perror("Memory allocation error");                      /* print an error message if memory allocation fails */
        exit(1);                                                /* exit the program with an error status */
    }

    printf("Main Sample Program Statistics:\n");   
    /* initial statistics */
    /* call mem_int on memory that was just grabbed */
    mem_init(global_memory, global_mem_size);                   /* initialize the memory allocator with the global memory pool */
    /* display initial statistic with a prefix of "after initialization" */ 
    print_stats("after initialization");     

    /* allocate and free blocks */
    {
        unsigned char *ptr_array[10];                           /* declare an array to hold pointers to allocated memory */
        unsigned int sizes[] = {50, 20, 20, 20, 50, 0};         /* array of sizes for memory allocation */

        /* loop through the sizes array and allocate memory, print statistics after each allocation */
        for (int i = 0; sizes[i] != 0; i++) {
            char buf[1024];       
            /* call malloc for all sizes in array */
            /* stash pointers that come back */
            ptr_array[i] = my_malloc(sizes[i]);                
            sprintf(buf, "after iteration: %d size %d", i, sizes[i]);  
            /* print statistic after every allocation */
            print_stats(buf);                                 
        }

        /* free memory allocated in random order in the ptr_array
        and print memory statistics after freeing memory */
        my_free(ptr_array[1]); print_stats("after free #1");  

        my_free(ptr_array[3]); print_stats("after free #3");   

        my_free(ptr_array[2]); print_stats("after free #2");  

        my_free(ptr_array[0]); print_stats("after free #0");   

        my_free(ptr_array[4]);  print_stats("after free #4");  
    
    }

    printf("\nProgram Functionality Tests Statistics:\n"); 
    /* run various test functions to test the reliability and functionality of the allocator */
    test_mem_init(global_memory, global_mem_size);
    test_allocate_more_than_available_memory(global_mem_size);
    test_allocate_free_random_sizes();  
    
    /* free global memory to ensure that any memory allocated during execution is
     properly released, preventing memory leaks */
    free(global_memory);

    return 0;   
}
