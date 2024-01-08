// #include <sys/param.h>
// #include <sys/bio.h>
#include <sys/bus.h>
// #include <sys/conf.h>
// #include <sys/kernel.h>
#include <sys/malloc.h>
// #include <sys/module.h>
// #include <sys/proc.h>
// #include <sys/lock.h>
// #include <sys/rwlock.h>
// #include <sys/mutex.h>
// #include <sys/systm.h>
// #include <sys/sysctl.h>
// #include <sys/vmmeter.h>
// #include <sys/eventhandler.h>

#include <sys/types.h>

// #include "smmu.h"

// #include <machine/bus.h>

// #include <vm/vm.h>
// #include <vm/pmap.h>
// #include <vm/vm_param.h>
// #include <vm/vm_object.h>
// #include <vm/vm_page.h>
// #include <vm/vm_pager.h>
// #include <vm/vm_phys.h>

// extern struct malloc_type type[1]

// struct malloc_type M_LUKE[1] = 
//       { { NULL, "", "Luke Memory", NULL } }; 


// MALLOC_DEFINE( M_LUKE, "Luke Memory", 
//                "Memory for the Luke subsystem" );



*contigmalloc(unsigned long size, struct malloc_type *type, int flags,
	    vm_paddr_t low, vm_paddr_t high, unsigned long alignment,
	    vm_paddr_t boundary) __malloc_like __result_use_check
	    __alloc_size(1) __alloc_align(6);

#define RTE_CONTIGMEM_DEFAULT_BUF_SIZE (512*1024*1024)
static int64_t     contigmem_buffer_size = RTE_CONTIGMEM_DEFAULT_BUF_SIZE;
#define	BUS_SPACE_MAXADDR	0xFFFFFFFF
// MALLOC_DEFINE(M_DEVBUF, "devbuf", "device driver memory");
// MALLOC_DEFINE(M_SMMU, "SMMU", SMMU_DEVSTR);
// MALLOC_DEFINE(M_CONTIGMEM, "contigmem", "contigmem(4) allocations");

// Writing a sample contig malloc 
// function to see if it can 
// allocate contigous memory
int main(void) {
    void *addr;
    addr = contigmalloc(contigmem_buffer_size, M_DEVBUF, M_ZERO,0, BUS_SPACE_MAXADDR, contigmem_buffer_size, 0);
}

