#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ gen_rand.cc -lm -o gen_rand.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen_rand.exe 3 10 3 4 > 002
./gen_rand.exe 10 20 4 5 > 003
./gen_rand.exe 1000 1000 0 10 0 > 004
./gen_rand.exe 1000 1000 0 10 1 > 005
./gen_rand.exe 2000 2000 0 10 0 > 006
./gen_rand.exe 2000 2000 0 10 1 > 007
./gen_rand.exe 5000 5000 1 10 0 > 008
./gen_rand.exe 5000 5000 1 10 1 > 009
./gen.exe 1 100 0 0 0 > 010
./gen.exe 100 500 0 0 0 > 011
./gen.exe 5000 5000 0 0 0 > 012
./gen.exe 5000 5000 1000000 1000000 0 > 013
./gen.exe 5000 5000 1000000 1000000 1 > 014
./gen.exe 2500 2500 500000 500000 > 015
./gen.exe 1000 1000 200000 200000 > 016
./gen.exe 1 10 1 10 0 > 017
./gen.exe 1 10 1 10 1 > 018
./gen.exe 10 50 1 10 0 > 019
./gen.exe 10 50 1 10 1 > 020
./gen.exe 100 200 100 200 0 > 021
./gen.exe 100 200 100 200 1 > 022
./gen.exe 200 500 100 200 0 > 023
./gen.exe 200 500 100 200 1 > 024
./gen.exe 1000 1000 0 10000 > 025
./gen.exe 1000 1000 0 100000 > 026
./gen.exe 2000 2000 0 10000 > 027
./gen.exe 2000 2000 0 100000 > 028
./gen.exe 5000 5000 10 10 > 029
./gen.exe 5000 5000 100 100 > 030
./gen.exe 5000 5000 1000 1000 > 031
./gen.exe 5000 5000 10000 10000 > 032
./gen.exe 5000 5000 100000 100000 > 033


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
