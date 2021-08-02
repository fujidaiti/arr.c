rm -rf ./dist
mkdir dist
cd dist
gcc -c ../src/arr.c
ar rc libarr.a arr.o
rm *.o
cp ../src/*.h .
cd ..