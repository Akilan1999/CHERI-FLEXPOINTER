# $CC $CFLAGS -I/home/akilan/cheri/output/morello-sdk/lib/clang/13.0.0/include/ -lpthread test.c 
# Working build code
$1 --config cheribsd-morello-purecap.cfg -lpthread matrix_multiply-pthreads.c

$1 --config cheribsd-morello-purecap.cfg -lpthread matrix_multiply-pthreads.c -o ../bin/matrix_multiply-pthreads-purecap.out
$1 --config cheribsd-morello-aarch64-for-hybrid-rootfs.cfg -lpthread matrix_multiply-pthreads.c -o ../bin/matrix_multiply-pthreads-hybrid-rootfs.out
$1 --config cheribsd-morello-aarch64-for-purecap-rootfs.cfg -lpthread matrix_multiply-pthreads.c -o ../bin/matrix_multiply-pthreads-purecap-rootfs.out
$1 --config cheribsd-morello-purecap-for-hybrid-rootfs.cfg -lpthread matrix_multiply-pthreads.c -o ../bin/matrix_multiply-pthreads-hybrid-rootfs.out
