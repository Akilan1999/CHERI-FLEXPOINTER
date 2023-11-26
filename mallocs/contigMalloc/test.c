#include	<sys/types.h>
#include	<sys/malloc.h>

// Ask for 8192 bytes of zero-filled memory	residing 
// between physical  address 0 and 4194303 
// inclusive, aligned to a 32K boundary	and 
// not	crossing a 1M address boundary.
void *p;
p = contigmalloc(8192, M_DEVBUF,	M_ZERO,	0, (1L << 22),32 *	1024, 1024 * 1024);

// To figure out free mechanism
// Reverse engineer the 
// contigmalloc kernel source code 
// and enable it to use userspace. 

// Investigate maximum bounds size 
// and how to be physically inside 
// bounds.

// Disable paging for the memory 
// allocation. 

// Prove how all of this can be
// part of the eager allocation.