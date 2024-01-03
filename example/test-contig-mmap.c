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

#define	MEMFD_NAME_PREFIX	"memfd:"


int main(void) {
        int memfd;
        void *mem_ro, *mem_rw; 

         printf("Here\n");

        // Create a memfd
        memfd = memfd_create_test("something", 0);
        if (memfd == -1) {
                perror("memfd_create failed");
                return 1;
        }

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

    printf("%u",MFD_HUGETLB);

	/* We've already validated that we're sufficiently sized. */
	snprintf(memfd_name, NAME_MAX + 1, "%s%s", MEMFD_NAME_PREFIX, name);
	oflags = O_RDWR;
	shmflags = 0;
	if ((flags & MFD_CLOEXEC) != 0)
		oflags |= O_CLOEXEC;
	// if ((flags & MFD_ALLOW_SEALING) != 0)
	// 	shmflags |= SHM_ALLOW_SEALING;
	// if ((flags & MFD_HUGETLB) != 0)
	// 	shmflags |= SHM_LARGEPAGE;
	// else
	// 	shmflags |= SHM_GROW_ON_WRITE;
    shmflags |= SHM_LARGEPAGE
	fd = __sys_shm_open2(SHM_ANON, oflags, 0, shmflags, memfd_name);
	// if (fd == -1 || (flags & MFD_HUGETLB) == 0)
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