# $CC $CFLAGS -I/home/akilan/cheri/output/morello-sdk/lib/clang/13.0.0/include/ -lpthread test.c 
# Working build code
$1 --config cheribsd-morello-purecap.cfg -lpthread linear_regression_pthreads.c -o ../bin/linear_regression_pthreads-purecap.out
$1 --config cheribsd-morello-aarch64-for-hybrid-rootfs.cfg -lpthread linear_regression_pthreads.c -o ../bin/linear_regression_pthreads-hybrid-rootfs.out
$1 --config cheribsd-morello-aarch64-for-purecap-rootfs.cfg -lpthread linear_regression_pthreads.c -o ../bin/linear_regression_pthreads-purecap-rootfs.out
$1 --config cheribsd-morello-purecap-for-hybrid-rootfs.cfg -lpthread linear_regression_pthreads.c -o ../bin/linear_regression_pthreads-hybrid-rootfs.out
