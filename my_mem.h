#ifndef MY_MEM_H
#define MY_MEM_H

/* macros for block status */
#define FREE_BLOCK 0
#define USED_BLOCK 1

/* alias to the structure data type that reports the memory block header size and status in bytes */
typedef struct {
    unsigned int size, status;                            
} block_header, *block_header_ptr;                                             /* create two new names for the struct type */

/* alias to the structure data type to report if memory stats are free or used */
typedef struct  {
    int num_blocks_used;
    int num_blocks_free;
    int smallest_block_free;
    int smallest_block_used;
    int largest_block_free;
    int largest_block_used;                                                        
} mem_stats_struct, *mem_stats_ptr;                                            /* create two new names for the struct type */

//main Functionality and Implementation Functions
void mem_init(unsigned char *my_memory, unsigned int my_mem_size);
void *my_malloc(unsigned size);
void my_free(void *mem_pointer);
void mem_get_stats(mem_stats_ptr mem_stats);
void print_stats(char *prefix);

#endif // MY_MEM_H