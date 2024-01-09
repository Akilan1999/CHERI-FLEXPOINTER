// #include <sys/param.h>
// #include <sys/bio.h>
// #include <sys/bus.h>
// #include <sys/conf.h>
// #include <sys/kernel.h>
// #include <sys/malloc.h>
// #include <sys/module.h>
// #include <sys/proc.h>
// #include <sys/lock.h>
// #include <sys/rwlock.h>
// #include <sys/mutex.h>
// #include <sys/systm.h>
// #include <sys/sysctl.h>
// #include <sys/vmmeter.h>
// #include <sys/eventhandler.h>

// #include <sys/types.h>

// #include "smmu.h"

// #include <machine/bus.h>

// #include <vm/vm.h>
// #include <vm/pmap.h>
// #include <vm/vm_param.h>
// #include <vm/vm_object.h>
// #include <vm/vm_page.h>
// #include <vm/vm_pager.h>
// #include <vm/vm_phys.h>

// __FBSDID("$FreeBSD$");

#include	<sys/types.h>
#include	<sys/malloc.h>
#include      <sys/kernel.h>

// extern struct malloc_type type[1]

// struct malloc_type M_LUKE[1] = 
//       { { NULL, "", "Luke Memory", NULL } }; 


// MALLOC_DEFINE( M_LUKE, "Luke Memory", 
//                "Memory for the Luke subsystem" );



// *contigmalloc(unsigned long size, struct malloc_type *type, int flags,
// 	    vm_paddr_t low, vm_paddr_t high, unsigned long alignment,
// 	    vm_paddr_t boundary) __malloc_like __result_use_check
// 	    __alloc_size(1) __alloc_align(6);

// #define	MALLOC_DEFINE(type, shortdesc, longdesc)			        \
// 	struct malloc_type type[1] = {					        \
// 		{							\
// 			.ks_next = NULL,				\
// 			.ks_version = M_VERSION,			\
// 			.ks_shortdesc = shortdesc,			\
// 		}							\
// 	};								\
// 	SYSINIT(type##_init, SI_SUB_KMEM, SI_ORDER_THIRD, malloc_init,	\
// 	    type);							\
// 	SYSUNINIT(type##_uninit, SI_SUB_KMEM, SI_ORDER_ANY,		\
// 	    malloc_uninit, type)

// MALLOC_DEFINE(M_MYDRIVER, "devbuf", "buffers used by my driver");

// #define	MALLOC_DEFINE(type, shortdesc, longdesc)			\
// 	struct malloc_type type[1] = {					\
// 		{							\
// 			.ks_next = NULL,				\
// 			.ks_version = M_VERSION,			\
// 			.ks_shortdesc = shortdesc,			\
// 		}							\
// 	};								\
// 	SYSINIT(type##_init, SI_SUB_KMEM, SI_ORDER_THIRD, malloc_init,	\
// 	    type);							\
// 	SYSUNINIT(type##_uninit, SI_SUB_KMEM, SI_ORDER_ANY,		\
// 	    malloc_uninit, type)

// #define RTE_CONTIGMEM_DEFAULT_BUF_SIZE (512*1024*1024)
// static int64_t     contigmem_buffer_size = RTE_CONTIGMEM_DEFAULT_BUF_SIZE;
// #define	BUS_SPACE_MAXADDR	0xFFFFFFFF
// MALLOC_DEFINE(M_DEVBUF, "devbuf", "device driver memory");
// MALLOC_DEFINE(M_SMMU, "SMMU", SMMU_DEVSTR);
// MALLOC_DEFINE(M_CONTIGMEM, "contigmem", "contigmem(4) allocations");

// Writing a sample contig malloc 
// function to see if it can 
// allocate contigous memory
int main(void) {
    const int pageSize = 4096;
        unsigned long size;
        void *ptr = NULL;
        unsigned long long t1, t2;
        int i = 0;
        unsigned long long avg_malloc = 0, avg_free = 0;
        int probes = 40;
        size = 2 * 1024 * 1024;

        for (i = 0; i < probes; i++) {

                t1 = rdtsc();
                ptr = contigmalloc(size, M_FOO, M_NOWAIT, 0, ~0,
                                   pageSize, 0);
                t2 = rdtsc();

                avg_malloc += t2 - t1;

                printf("contigmalloc cycles: %llu\n", t2-t1);

                if (ptr == NULL)
                        return;

                t1 = rdtsc();
                contigfree(ptr, size, M_FOO);
                t2 = rdtsc();
                avg_free += t2 - t1;
                printf("contigfree cycles: %llu\n\n", t2-t1);
                uprintf("Loop complete\n");
        }

        printf("contigmalloc %llu contigfree %llu\n", avg_malloc / probes, avg_free / probes);  
}

