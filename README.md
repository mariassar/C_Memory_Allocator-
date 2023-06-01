# C Memory Allocator
My goal was to make a basic but functional implementation of a memory allocator in the C programming Lnguage The standard C programming environment includes an elaborate memory allocator accessed via malloc() and free().


To accomplish my goal, I needed to write my own version of malloc() and free() using a data structure that would allow me to optimally organize memory space into several parts that can be used and reused . My makeFile compliles the c program into the file called mem containing the output of the memory allocation simulating program.

my_mem.c =
The data structure supporting the allocator is a linked list of memory block headers.
The strategy for allocation was "first fit", meaning the first block of sufficient size is taken. (sequential manner) If size is not less than the required size then it is allocated.
The probgram breaks the bulk space malloc() into blocks with headers. 
Each block gets the size and the status (free, used) 
By jumping to the +size in memory location from the block, you get to the next block (and its header)
To collect the information about memory through a singly linked list the code goes through the chain of those blocks and marks their sizes and statuses (free vs occupied). Once the pointer is beyond the pre-allocated bulk it breaks from allocating. 
o allocate, find the first free block of the sufficient size, and split it into two blocks: occupied and the remaining free. If the size is not big enough for the block plus an additional header for the new block, I mark this block as occupied without splitting .
To free, identify the block, and mark as free. Next the code finds the next block ( + size) and if it is free, merges both blocks by extending the size of the current freed block. Going from the start of the chain the code locates the previous block and if it is free, it extends it too. 

The make file prints the output to mem.

$ make && ./mem
mem.pdf = To get the final graph: I created two dictionaries to put the x and y coordinates in. I used matplotlib to create a scatterplot figure of these points that later creates a pdf called graph.pdf.

testfile = he make file prints this datato the file called zip.

Sucsessful output and testing:

PResentation
The Best Case performance for malloc and free is O(1) if the the block is at the beginning of the list.
Either malloc quickly finds the free block of the correct size, or free deallocates the block at the beginning of the chain of blocks.
The Worst Case the functions have to go through the entire linked list of blocks and the performance is O(n), where n is the number of free or used blocks in the chain.
The Average Case performance would depend on the requests for malloc and free from the main function, but in general the average should be O(n/2).
