#define _GNU_SOURCE
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/filio.h>
#include <sys/mman.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "libc_private.h"

// #ifndef MAP_HUGETLB
// #define MAP_HUGETLB 0x40
// #endif

/* Only ia64 requires this */
// #ifdef __ia64__
// #define ADDR (void *)(0x8000000000000000UL)
// #define FLAGS (MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_FIXED)
// #else
// #define ADDR (void *)(0x0UL)
// #define FLAGS (MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB)
// #endif

// Allocation information 

typedef uintptr_t paddr_t;
typedef uintptr_t vaddr_t;


struct image_info {
    /* Start/end byte of the image in physical memory. */
    paddr_t phys_region_start;
    paddr_t phys_region_end;

    /* Start/end byte in virtual memory the image requires to be located. */
    vaddr_t virt_region_start;
    vaddr_t virt_region_end;

    /* Virtual address of the user image's entry point. */
    vaddr_t  virt_entry;

    /* The seL4 kernel boot interface does not have the parameter virt_entry,
     * but expect a parameter with the offset between the physical and virtual
     * addresses of the image, where this must hold:
     *     virt_address + phys_virt_offset = phys_address
     * Practically, the offset is usually a positive value, because the virtual
     * address is a low value and the actually physical address is much greater.
     * But in general, there is no restrictions on the physical and virtual
     * image location. Defining phys_virt_offset as a signed value might seem
     * the intuitive choice how to handle this, but there is are two catches
     * here that break the C rules. We can't cover the full integer range then
     * and overflows/underflows are well defined for unsigned values only. They
     * are undefined for signed values, even if such operations practically work
     * in many cases due to how the compiler/machine implements negative
     * integers using the two's-complement.
     * Assume 32-bit system with virt_address=0xc0000000 and phys_address=0,
     * then phys_virt_offset would have to be -0xc0000000. This value is not
     * in the 32-bit signed integer range. With unsigned integers, calculating
     * 0 - 0xc0000000 results in 0x40000000 after an underflow, the reverse
     * calculation 0xc0000000 + 0x40000000 results in 0 again after overflow. If
     * 0x40000000 is a signed integer, result is likely the same, but the whole
     * operation is completely undefined by C rules.
     */
    word_t phys_virt_offset;
};


#define	MEMFD_NAME_PREFIX	"memfd:"

int	memfd_create(const char *, unsigned int);


int main(void) {
        int memfd;
        void *mem_ro, *mem_rw; 

         printf("Here\n");

        // Create a memfd
        memfd = memfd_create_test("something", 0);
         printf("%d \n",memfd);
        if (memfd == -1) {
                perror("memfd_create_test failed");
                return 1;
        }

        printf("After memfd\n");

        // Give the file a size, otherwise reading/writing will fail
        if (ftruncate(memfd, 0x1000) == -1) {
                perror("ftruncate failed");
                return 1; 
        }

        // Map the fd as read only and private
        mem_ro = mmap(NULL, 0x1000, PROT_READ, MAP_PRIVATE, memfd, 0);
        if (mem_ro == MAP_FAILED) {
                perror("mmap failed");
                return 1;
        }

        // Map the fd as read/write and shared (shared is needed if we want
        // write operations to be propagated to the other mappings)
        mem_rw = mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, 0);
        if (mem_rw == MAP_FAILED) {
                perror("mmap failed");
                return 1;
        }

        printf("ro mapping @ %p\n", mem_ro);
        printf("rw mapping @ %p\n", mem_rw);

        // This write can now be read from both mem_ro and mem_rw
        *(char *)mem_rw = 123;

        // Test reading
        printf("read from ro mapping: %d\n", *(char *)mem_ro);
        printf("read from rw mapping: %d\n", *(char *)mem_rw);

        return 0;
}


/*
 * The path argument is passed to the kernel, but the kernel doesn't currently
 * do anything with it.  Linux exposes it in linprocfs for debugging purposes
 * only, but our kernel currently will not do the same.
 */
int
memfd_create_test(const char *name, unsigned int flags)
{
    printf("Test\n");
	char memfd_name[NAME_MAX + 1];
	size_t namelen, *pgs, pgsize;
	struct shm_largepage_conf slc;
	int error, fd, npgs, oflags, pgidx, saved_errno, shmflags;

	if (name == NULL) {
		errno = EBADF;
		return (-1);
	}
	namelen = strlen(name);
	if (namelen + sizeof(MEMFD_NAME_PREFIX) - 1 > NAME_MAX) {
		errno = EINVAL;
		return (-1);
	}
	if ((flags & ~(MFD_CLOEXEC | MFD_ALLOW_SEALING | MFD_HUGETLB |
	    MFD_HUGE_MASK)) != 0) {
		errno = EINVAL;
		return (-1);
	}
	/* Size specified but no HUGETLB. */
	if ((flags & MFD_HUGE_MASK) != 0 && (flags & MFD_HUGETLB) == 0) {
		errno = EINVAL;
		return (-1);
	}

    printf("%u \n",MFD_HUGETLB);

	/* We've already validated that we're sufficiently sized. */
	snprintf(memfd_name, NAME_MAX + 1, "%s%s", MEMFD_NAME_PREFIX, name);
	oflags = O_RDWR;
	shmflags = 0;
	if ((flags & MFD_CLOEXEC) != 0)
		oflags |= O_CLOEXEC;
	// if ((flags & MFD_ALLOW_SEALING) != 0)
	// shmflags |= SHM_ALLOW_SEALING;
	// if ((flags & MFD_HUGETLB) != 0)
	// 	shmflags |= SHM_LARGEPAGE;
	// else
	// 	shmflags |= SHM_GROW_ON_WRITE;
    // shmflags |= SHM_LARGEPAGE;
	fd = __sys_shm_open2(SHM_ANON, oflags, 0, shmflags, memfd_name);
	// if (fd == -1 || (flags & MFD_HUGETLB) == 0)
     printf("%d \n", fd);

     return (fd);

	// pgs = NULL;
	// npgs = getpagesizes(NULL, 0);
	// if (npgs == -1)
	// 	goto clean;
	// pgs = calloc(npgs, sizeof(size_t));
	// if (pgs == NULL)
	// 	goto clean;
	// error = getpagesizes(pgs, npgs);
	// if (error == -1)
	// 	goto clean;
	// pgsize = (size_t)1 << ((flags & MFD_HUGE_MASK) >> MFD_HUGE_SHIFT);
	// for (pgidx = 0; pgidx < npgs; pgidx++) {
	// 	if (pgsize == pgs[pgidx])
	// 		break;
	// }
	// if (pgidx == npgs) {
	// 	errno = EOPNOTSUPP;
	// 	goto clean;
	// }
	// free(pgs);
	// pgs = NULL;

	// memset(&slc, 0, sizeof(slc));
	// slc.psind = pgidx;
	// slc.alloc_policy = SHM_LARGEPAGE_ALLOC_DEFAULT;
	// error = ioctl(fd, FIOSSHMLPGCNF, &slc);
	// if (error == -1)
	// 	goto clean;
	// return (fd);

clean:
	saved_errno = errno;
	close(fd);
	free(pgs);
	errno = saved_errno;
	return (-1);
}