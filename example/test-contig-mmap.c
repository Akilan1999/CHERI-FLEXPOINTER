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


int main(void) {
        int memfd;
        void *mem_ro, *mem_rw;

        print(MFD_HUGETLB)

        // Create a memfd
        memfd = memfd_create("something", MFD_HUGETLB);
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