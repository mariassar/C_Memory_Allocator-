#include <stdio.h>
#include <stdlib.h>

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

/* pointer to the memory pool and its size that is setup by mem_init function */
unsigned char *pool = NULL;
unsigned int pool_size = 0;

/* The memory to be managed is passed into this function */
/* mem_init saves the pointer to memory and initializes the size and status of a given block */
void mem_init(unsigned char *my_memory, unsigned int my_mem_size) {
    /* save the provided memory block into global variables */
    pool = my_memory;                                                         /* holds the pointer to the memory pool's pointer ( my_memory -> global memory -> malloc() ) */
    pool_size = my_mem_size;                                                  /* holds the pointer to the memory pool's size */
    if (pool != NULL) {                                                       /* if we got a valid pool(array/linked list) */
        block_header_ptr first = (block_header_ptr)pool;
        first->size = my_mem_size;                                            /* take the structure's initial size and set the block to the memory pool's full size */
        first->status = FREE_BLOCK;                                           /* take the structure's initial status and set the block to free */ 
    }
}

/* a function functionally equivalent to malloc() , but allocates it from the memory pool passed to mem_init() */
void *my_malloc(unsigned size) {
    unsigned char *temp = pool;                                              /* get to the beginning of the memory pool */
    unsigned int needSize = size + sizeof(block_header);                     /* look for the size needed meaning the header plus the size of the block given by main */
    block_header_ptr b = (block_header_ptr)temp;                             /* set on the first header at the beginning of the pool */
    while (temp - pool < pool_size) {                                        /* temp pointer should not run beyond the pool size */
        if (b->status == FREE_BLOCK && b->size >= needSize) {
            break;                                                           /* break as soon as a free block of the necessary size found "first fit strategy " */
        }
        temp += b->size;                                                     /* increment temp pointer by the block size, this should land it to the next block header */
        b = (block_header_ptr)temp;
    }
    if (temp - pool >= pool_size) {
       return NULL;                                                          /* if no free block is found, temp will be beyond the pool, return NULL, no allocation */
    }
    /* free block is located */
    b->status = USED_BLOCK;                                                 /* make the block as used */
    if (needSize + sizeof(block_header) < b->size) {                        /* if the block is larger than the needSize + header for the new block, split the excess into the next free block */
        block_header_ptr split_block = (block_header_ptr)(temp + needSize); /* set a pointer to where the new block header will start */
        split_block->size =  b->size - needSize;                            /* set the size of the split block to the difference */
        split_block->status = FREE_BLOCK;                                   /* mark this new block as free */
        b->size = needSize;                                                 /* update the size of the allocated block, to set where the new free block begins */
    }
                                                                            /* if the size of the block is exactly how much free space is left, no need to split, just return it */
    return temp + sizeof(block_header);                                     /* return a pointer to the memory after the header */
}

/* a function equivalent to free(), but returns the memory to the pool passed to mem_init() */
void my_free(void *mem_pointer) {
    /* variables to walk through the memory headers */
    unsigned char *prev=NULL;                                               /* previous header */
    unsigned char *cur=pool;                                                /* current header */

    /*  a pointer is passed to the memory inside the block, minus the  header size to get the pointer to the header */
    unsigned char *need = ((unsigned char*)mem_pointer) - sizeof(block_header);
    block_header_ptr b = (block_header_ptr)cur;

    /* try to locate the needed pointer in the chain of memory blocks */
    /* start from the first block (pool poitner) and increment by the block size */
    while (cur - pool < pool_size && cur < need) {                          /* loop until we run beyond the memory pool or the needed pointer is found */
        prev = cur;                                                         /* set the pointer(prev) to the previous block(cur) */
        cur += b->size;                                                     /* increment the current header to the next block */
        b = (block_header_ptr)cur;                                          /* create a pointer to the block header */
    }
    /* if we locate the memory successfully then the current header should be exactly equal to the need pointer */
    if (cur == need) {                                                      /* if we found the block we need */
        unsigned char *next=cur + b->size;                                  /* obtain the pointer to the next block */
        b->status = FREE_BLOCK;                                             /* mark the block as free */
        if (next - pool < pool_size) {                                      /* check if the next block exists  */
            block_header_ptr bnext = (block_header_ptr)next;
            if (bnext->status == FREE_BLOCK) {                              /* if the next block is free, merge it to the current block */
                b->size += bnext->size;                                     /* extend the current block size to cover the next free block */
            }
        }
        /* check the to see if the prev block exists */
        if (prev != NULL) {
            block_header_ptr bprev = (block_header_ptr)prev;
            if (bprev->status == FREE_BLOCK) {                              /* if the previous block is free, then extend it to cover all free space */
                bprev->size += b->size;
            }
        }
        
    }
}


/* the function goes through every memory block and collects statistics about the current allocation of the memory pool. */
void mem_get_stats(mem_stats_ptr mem_stats) {
    /* setup the variables before collecting stats */
    mem_stats->largest_block_free = 0;               
    mem_stats->smallest_block_free = (int)pool_size; 
    mem_stats->num_blocks_free = 0;                  
    mem_stats->num_blocks_used = 0;                  
    mem_stats->largest_block_used = 0;               
    mem_stats->smallest_block_used = (int)pool_size; 
    
    {
        unsigned char *temp = pool;                                        /* a pointer to get the pool block by block */
        while (temp - pool < pool_size) {                                  /* while the pointer is within the pool */
            block_header_ptr b = (block_header_ptr)temp;                   /* set temporary pointer to header of the current block */
            int cleanSize = (int)(b->size - sizeof(block_header));         /* get block size (size - header) becuase main didnt give us the header */
            switch (b->status) {                                           /* check the block status */
                case FREE_BLOCK:
                /* update free block stats */
                    mem_stats->num_blocks_free++;                          /* add one to how many blocks are free */
                    if (cleanSize > mem_stats->largest_block_free) {       /* if the clean size of the block is greater than the largest free block */
                        mem_stats->largest_block_free = cleanSize;         /* set the largest free block eqaul to the clean size */
                    }
                    if (cleanSize < mem_stats->smallest_block_free) {      /* if the clean size of the block is less than the smallest free block */
                        mem_stats->smallest_block_free = cleanSize;        /* set the smallest free block eqaul to the clean size */
                    }
                    break;
                /* update used block stats */
                case USED_BLOCK:
                    mem_stats->num_blocks_used++;                          /* add one to how many blocks are used */
                    if (cleanSize > mem_stats->largest_block_used) {       /* if the clean size of the block is greater than the largest used block */
                        mem_stats->largest_block_used = cleanSize;         /* set the largest used block eqaul to the clean size */
                    }
                    if (cleanSize < mem_stats->smallest_block_used) {      /* if the clean size of the block is less than the smallest used block */
                        mem_stats->smallest_block_used = cleanSize;        /* set the smallest used block eqaul to the clean size */
                    }
                    break;
                default:
                    break;
            }
            temp += b->size;
        }
        /* set the smallest sizes of used and free blocks to 0 if no block was found */
        if (mem_stats->num_blocks_free == 0) {
            mem_stats->smallest_block_free = 0;
        }
        if (mem_stats->num_blocks_used == 0) {
            mem_stats->smallest_block_used = 0;
        }
    }
}

 /* function to print stats collected */
void print_stats(char *prefix) {
    mem_stats_struct mem_stats;
    /* calls function to get stats to be printed */
    mem_get_stats(&mem_stats);
    printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
           prefix,
           mem_stats.num_blocks_free,
           mem_stats.num_blocks_used,
           mem_stats.smallest_block_free,
           mem_stats.largest_block_free,
           mem_stats.smallest_block_used,
           mem_stats.largest_block_used);

}

int main(int argc, char **argv)
{
    unsigned int global_mem_size = 1024 * 1024;
    /* grabs memory from malloc */
    unsigned char *global_memory = malloc(global_mem_size);
    
    /* call mem_int on memory that was just grabbed */
    mem_init(global_memory, global_mem_size);
    
    /* dump initial statistic with a prefix of init */ 
    /* init tells us which state the prefix is in when being printed */
    print_stats("init");
       
    unsigned char *ptr_array[10];
    unsigned int sizes[] = {50, 20, 20, 20, 50, 0};

    for (int i = 0; sizes[i] != 0; i++) {
        char buf[1024];
        /* call malloc for all sizes in array */
        /* stash pointers that come back */
        ptr_array[i] = my_malloc(sizes[i]);
        
        sprintf(buf, "after iteration %d size %d", i, sizes[i]);
        /* print statistic after every allocation */
        print_stats(buf);
    }
    /* free up in random order */
    my_free(ptr_array[1]);  print_stats("after free #1");
    my_free(ptr_array[3]);  print_stats("after free #3");
    my_free(ptr_array[2]);  print_stats("after free #2");
    my_free(ptr_array[0]);  print_stats("after free #0");
    my_free(ptr_array[4]);  print_stats("after free #4");
    
    free(global_memory);
    return 0;
}
