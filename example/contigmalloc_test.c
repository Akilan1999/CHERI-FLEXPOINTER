#include	<sys/types.h>
#include	<sys/malloc.h>

// MALLOC_DEFINE(M_DEVBUF, "devbuf", "device driver memory");

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
                ptr = contigmalloc(size, M_DEVBUF, M_NOWAIT, 0, ~0,
                                   pageSize, 0);

                if (ptr == NULL)
                        break;

                contigfree(ptr, size, M_DEVBUF);
        }
}

