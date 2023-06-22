#include <assert.h>

int main() {

    unsigned int global_mem_size = 1024 * 1024;
    unsigned char *global_memory = malloc(global_mem_size);
    
    mem_init(global_memory, global_mem_size);
    print_stats("Init");
    
    // Test Case 1: Allocate and deallocate multiple blocks
    unsigned char *ptr1 = (unsigned char *)my_malloc(100);
    unsigned char *ptr2 = (unsigned char *)my_malloc(200);
    unsigned char *ptr3 = (unsigned char *)my_malloc(300);
    
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);
    assert(ptr3 != NULL);
    
    print_stats("After allocation");
    
    my_free(ptr2);
    print_stats("After deallocation");
    
    my_free(ptr1);
    my_free(ptr3);
    
    print_stats("After all deallocations");
    
    // Test Case 2: Allocate and deallocate in random order
    unsigned char *ptr_array[5];
    unsigned int sizes[] = {50, 20, 30, 40, 60};
    
    for (int i = 0; i < 5; i++) {
        ptr_array[i] = (unsigned char *)my_malloc(sizes[i]);
        assert(ptr_array[i] != NULL);
    }
    // Test Case 3: Allocate and deallocate large blocks
    unsigned char *ptr4 = (unsigned char *)my_malloc(800000);
    unsigned char *ptr5 = (unsigned char *)my_malloc(500000);
    
    assert(ptr4 != NULL);
    assert(ptr5 != NULL);
    
    print_stats("After large allocations");
    
    my_free(ptr4);
    print_stats("After large deallocation");

    my_free(ptr5);
    print_stats("After all deallocations");

    // Test Case 4: Allocate and deallocate multiple blocks with splitting
    unsigned char *ptr6 = (unsigned char *)my_malloc(200);
    unsigned char *ptr7 = (unsigned char *)my_malloc(400);
    unsigned char *ptr8 = (unsigned char *)my_malloc(600);
    
    assert(ptr6 != NULL);
    assert(ptr7 != NULL);
    assert(ptr8 != NULL);
    
    print_stats("After allocation with splitting");
    
    my_free(ptr7);
    print_stats("After deallocation with splitting");

    my_free(ptr6);
    my_free(ptr8);
    
    print_stats("After all deallocations");

    // Test Case 5: Allocate maximum-sized block
    unsigned char *ptr9 = (unsigned char *)my_malloc(pool_size - sizeof(block_header));
    assert(ptr9 != NULL);

    print_stats("After maximum allocation");

    my_free(ptr9);
    print_stats("After deallocation of maximum block");
    
    print_stats("After random allocations");
    
    my_free(ptr_array[1]);
    my_free(ptr_array[3]);
    my_free(ptr_array[0]);
    my_free(ptr_array[4]);
    my_free(ptr_array[2]);
    
    print_stats("After random deallocations");
    
    free(global_memory);
    return 0;


}

#Test allocating the maximum available memory:

#Allocate the entire memory pool using my_malloc() (e.g., my_malloc(pool_size - sizeof(block_header))).
#Verify that the allocation is successful and that the memory stats reflect the entire pool being used.
#Test allocating more memory than available:

#Allocate memory that exceeds the size of the memory pool using my_malloc().
#Verify that the allocation fails (returns NULL) and that the memory stats remain unchanged.
#Test freeing and reusing memory blocks:

#Allocate a memory block using my_malloc() and store the returned pointer.
#Free the memory block using my_free().
#Allocate another memory block with the same size using my_malloc().
#Verify that the second allocation is successful and that the memory stats reflect the correct block status and sizes.
#Test allocating and freeing multiple blocks in different orders:

#Allocate several memory blocks using my_malloc() and store the returned pointers.
#Free the memory blocks in different orders using my_free().
#Verify that the memory stats are correctly updated after each allocation and deallocation.
#Test edge cases with small memory sizes:

#Set a small memory pool size (e.g., 32 bytes) using mem_init().
#Allocate and free memory blocks of various sizes using my_malloc() and my_free().
#Verify that the memory stats accurately reflect the available memory and block sizes.
