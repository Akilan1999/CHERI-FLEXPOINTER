project(CHERI_FLEXPOINTER)
set(CMAKE_CXX_STANDARD 14)

include_directories(jemalloc/include)
include_directories(jemalloc/include/jemalloc)
include_directories(jemalloc/include/jemalloc/internal)

target_link_libraries(cheri_caprevoke)

# build jemalloc
set(JEMALLOC_SRC jemalloc.c arena.c background_thread.c base.c bin.c
        bitmap.c ckh.c ctl.c div.c extent.c extent_dss.c extent_mmap.c hash.c
        hook.c large.c log.c malloc_io.c mutex.c mutex_pool.c nstime.c
        pages.c prng.c prof.c rtree.c stats.c sz.c tcache.c ticker.c tsd.c
        witness.c)
list(TRANSFORM JEMALLOC_SRC PREPEND ./jemalloc/src/)
add_library(jemalloc SHARED ${JEMALLOC_SRC})
target_include_directories(jemalloc PRIVATE . ./jemalloc/include)