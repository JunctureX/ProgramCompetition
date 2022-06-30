#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 1 10 10 1 > 002
./gen.exe 10 10 10 1 > 003
./gen.exe 100 100 100 1 > 004
./gen.exe 1000 2000 10000 1 > 005
./gen.exe 1000 2000 100000 1 > 006
./gen.exe 10000 20000 100000 1 > 007
./gen.exe 50000 50000 100000 1 > 008
./gen.exe 50000 50000 1000000 1 > 009
./gen.exe 50000 50000 10000000 1 > 010
./gen.exe 50000 50000 10000000 10 > 011
./gen.exe 50000 50000 10000000 100 > 012
./gen.exe 50000 50000 10000000 1000 > 013
./gen.exe 50000 50000 10000000 10000 > 014
./gen.exe 50000 50000 1000000000 1 > 015
./gen.exe 50000 50000 1000000000 10 > 016
./gen.exe 50000 50000 1000000000 100 > 017
./gen.exe 50000 50000 1000000000 1000 > 018
./gen.exe 50000 50000 1000000000 10000 > 019


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
