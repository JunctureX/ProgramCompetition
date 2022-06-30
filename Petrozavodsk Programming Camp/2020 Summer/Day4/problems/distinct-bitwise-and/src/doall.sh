#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ gen_max.cc -lm -o gen_max.exe -O2 -static --std=c++0x || exit 1
g++ gen_rand.cc -lm -o gen_rand.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen_rand.exe 1 10 0 100 > 002
./gen_rand.exe 20 50 0 10000 > 003
./gen_rand.exe 10 100 0 1000000000 > 004
./gen_rand.exe 100 1000 0 1000000000000000000 > 005
./gen_rand.exe 1000 1000 0 1000000000000000000 > 006
./gen_rand.exe 5000 5000 0 1000000000000000000 0 > 007
./gen_rand.exe 5000 5000 0 1000000000000000000 1 > 008
./gen_rand.exe 5000 5000 0 1000000000000000000 2 > 009
./gen_rand.exe 5000 5000 0 1000000000000000000 3 > 010
./gen_max.exe 5000 5000 576460752303423487 576460752303423487 > 011
./gen_max.exe 5000 5000 0 0 > 012
./gen_max.exe 5000 5000 0 1000000000000000000 0 > 013
./gen_max.exe 5000 5000 0 1000000000000000000 1 > 014
./gen_max.exe 1 10 0 1000000000000000000 > 015
./gen_max.exe 20 50 0 1000000000000000000 > 016
./gen_max.exe 10 100 0 1000000000000000000 > 017
./gen.exe 1 100 0 1000000000000000000 > 018
./gen.exe 100 500 0 1000000000000000000 > 019
./gen.exe 1000 1000 0 1000000000000000000 > 020


mkdir ../tests
for i in ???;do
echo Validating $i
./validator.exe <$i || exit 1
echo Generating $i.a
./sol.exe <$i >../tests/$i.a || exit 1
mv $i ../tests/$i
done
rm *.exe
rm *.class
