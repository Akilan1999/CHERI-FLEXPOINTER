cmake_minimum_required(VERSION 3.25)
project(CHERI_FLEXPOINTER)

set(CMAKE_CXX_STANDARD 14)

include_directories(benchmark/histogram)
include_directories(benchmark/kmeans)
include_directories(benchmark/linear_regression)
include_directories(benchmark/matrix_multiply)
include_directories(jemalloc/include)
include_directories(jemalloc/include/jemalloc)
include_directories(jemalloc/include/jemalloc/internal)
include_directories(jemalloc/src/tlb-sim)
include_directories(jemalloc/src/tlb-sim/preprocess)

# build jemalloc
set(JEMALLOC_SRC jemalloc.c arena.c background_thread.c base.c bin.c
        bitmap.c ckh.c ctl.c div.c extent.c extent_dss.c extent_mmap.c hash.c
        hooks.c large.c log.c malloc_io.c mutex.c mutex_pool.c nstime.c
        pages.c prng.c prof.c rtree.c stats.c sz.c tcache.c ticker.c tsd.c
        witness.c)
list(TRANSFORM JEMALLOC_SRC PREPEND ./jemalloc/src/)
add_library(jemalloc SHARED ${JEMALLOC_SRC})
target_include_directories(jemalloc PRIVATE . ./jemalloc/include)