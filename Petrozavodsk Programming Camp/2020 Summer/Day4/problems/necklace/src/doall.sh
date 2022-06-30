#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ checker.cc -lm -o checker.exe -O2 -static --std=c++0x || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 1 10 10 0 > 002
./gen.exe 1 10 10 1 > 003
./gen.exe 1 10 10 3 > 004
./gen.exe 10 50 10 0 > 005
./gen.exe 100 200 1000 0 > 006
./gen.exe 1000 2000 10000 0 > 007
./gen.exe 1000 2000 10000 1 > 008
./gen.exe 1000 2000 10000 2 > 009
./gen.exe 1000 2000 10000 3 > 010
./gen.exe 1000 2000 10000 4 > 011
./gen.exe 10000 20000 1000000 0 > 012
./gen.exe 10000 20000 1000000 1 > 013
./gen.exe 10000 20000 1000000 2 > 014
./gen.exe 10000 20000 1000000 3 > 015
./gen.exe 10000 20000 1000000 4 > 016
./gen.exe 50000 100000 1000000000 0 0 > 017
./gen.exe 50000 100000 1000000000 0 1 > 018
./gen.exe 200000 200000 1000000000 0 0 > 019
./gen.exe 200000 200000 1000000000 0 1 > 020
./gen.exe 200000 200000 1000000000 0 2 > 021
./gen.exe 200000 200000 1000000000 0 3 > 022
./gen.exe 200000 200000 1000000000 4 0 > 023
./gen.exe 200000 200000 1000000000 4 1 > 024
./gen.exe 200000 200000 1000000000 4 2 > 025
./gen.exe 200000 200000 1000000000 4 3 > 026


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
