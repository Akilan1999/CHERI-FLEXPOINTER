#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __USE_GNU
#  define __USE_GNU
#endif

#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <stdint.h>
#include <string.h> /* for memcpy hack below */
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FILENAME "/dev/contigmem"

int main(int argc, char **argv)
{ 
  // 1 GB 
  // size_t size = 1000000000;
  
  // smaller size
  size_t size = 1000000;

  // Custom malloc
  int fd = open
	(FILENAME, O_RDWR | O_CREAT, 0600);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

  // Cannot read in security exception 
  // on reads
  // struct stat st;
  // stat(FILENAME, &st);
  // size = st.st_size;
  // printf(size);


	off_t offset = 0; // offset to seek to.

	if (ftruncate(fd, size) < 0) {
		perror("ftruncate");
		close(fd);
		exit(EXIT_FAILURE);
	}

	int *ptr = mmap(NULL, size,
	                         PROT_READ | PROT_WRITE, MAP_SHARED,
	                         fd, offset);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

    *ptr = size;


  printf("Successfully malloc'd %zu bytes at addr %p\n", size, ptr);
  assert(ptr != NULL);

  // Custom free 
  // int *pt = ptr;
  //   // size_t size;
  //   --pt;
  //   size = *pt;
  //   if(munmap(pt, size) == -1)
	// {
	// 	perror("munmap");
	// 	exit(EXIT_FAILURE);
  // }

  printf("Successfully free'd %zu bytes from addr %p\n", size, ptr);
  return 0;
}

static inline void *MALLOC(size_t size)
{
//    void * temp = malloc(size);
//    assert(temp);
//    return temp;

// Ensuring malloc this is mmap and phyiscally contigous
    int fd = open
	(FILENAME, O_RDWR | O_CREAT, 0600);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	off_t offset = 0; // offset to seek to.

	if (ftruncate(fd, size) < 0) {
		perror("ftruncate");
		close(fd);
		exit(EXIT_FAILURE);
	}

	int *ptr = mmap(NULL, size,
	                         PROT_READ | PROT_WRITE, MAP_SHARED,
	                         fd, offset);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

    *ptr = size;

    return ptr;
   // void *ptr = malloc(size);
   // return ptr;
}


static inline void *FREE(void *ptr)
{
    int *pt = ptr;
    size_t size;
    --pt;
    size = *pt;
    if(munmap(pt, size) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
   // free(ptr);
}