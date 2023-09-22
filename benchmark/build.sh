mkdir bin

 # Example for compiler path
 # /home/akilan/cheri/output/morello-sdk/bin/clang

cd histogram/
sh build.sh $1
cd ..

cd kmeans/
sh build.sh $1
cd ..

cd linear_regression/
sh build.sh $1
cd ..

cd matrix_multiply/
sh build.sh $1
cd ..

# Copy benchmark to bin/ folder 
cp benchmark.sh bin/benchmark.sh