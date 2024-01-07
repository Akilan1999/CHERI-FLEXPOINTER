#include	<sys/types.h>
#include	<sys/malloc.h>

MALLOC_DEFINE(M_CONTIGMEM, "contigmem", "contigmem(4) allocations");
static int64_t     contigmem_buffer_size = RTE_CONTIGMEM_DEFAULT_BUF_SIZE;
#define	BUS_SPACE_MAXADDR	0xFFFFFFFF

// Writing a sample contig malloc 
// function to see if it can 
// allocate contigous memory
int main(void) {
    void *addr;
    addr = contigmalloc(contigmem_buffer_size, M_CONTIGMEM, M_ZERO,0, BUS_SPACE_MAXADDR, contigmem_buffer_size, 0);
}

