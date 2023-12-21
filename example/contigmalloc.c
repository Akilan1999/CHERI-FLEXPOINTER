#include	<sys/types.h>
#include	<sys/malloc.h>


void *p;
       p = contigmalloc(8192, M_DEVBUF,	M_ZERO,	0, (1L << 22),
       32 *	1024, 1024 * 1024);
