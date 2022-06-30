#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 10 10 1 10 2 > 002
./gen.exe 100 100 1 100 2 1 > 003
./gen.exe 1000 1000 1 1000 2 2 > 004
./gen.exe 10000 10000 1 10000 2 3 > 005
./gen.exe 100000 100000 1 100000 2 0 > 006
./gen.exe 100000 100000 1 100000 2 1 > 007
./gen.exe 1000000 1000000 1000 1000 0 > 008
./gen.exe 1000000 1000000 1000 1000 1 > 009
./gen.exe 1000000 1000000 1 1 0 > 010
./gen.exe 1000000 1000000 1 1 1 > 011
./gen.exe 1000000 1000000 2 2 0 > 012
./gen.exe 1000000 1000000 2 2 1 > 013
./gen.exe 1000000 1000000 1000 1000 2 0 > 014
./gen.exe 1000000 1000000 1000 1000 2 1 > 015
./gen.exe 1000000 1000000 1000 1000 2 2 > 016
./gen.exe 1000000 1000000 1000 1000 2 3 > 017
./gen.exe 1000000 1000000 1000 1000 2 4 > 018
./gen.exe 1000000 1000000 1 10 2 0 > 019
./gen.exe 1000000 1000000 1 10 2 1 > 020
./gen.exe 1000000 1000000 1 10 2 2 > 021
./gen.exe 1000000 1000000 1 10 2 3 > 022
./gen.exe 1000000 1000000 1 10 2 4 > 023
./gen.exe 1000000 1000000 20000 20000 2 > 024
./gen.exe 1000000 1000000 25000 25000 2 > 025
./gen.exe 1000000 1000000 33333 33333 2 > 026
./gen.exe 1000000 1000000 100000 100000 2 > 027
./gen.exe 1000000 1000000 1000000 1000000 2 > 028


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
