#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ gen2.cc -lm -o gen2.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 1 1 10 > 002
./gen.exe 10 1 10 > 003
./gen.exe 100 1 10 > 004
./gen.exe 1000 1 10 > 005
./gen.exe 10000 1 10 > 006
./gen.exe 1 10 100 > 007
./gen.exe 10 10 100 > 008
./gen.exe 100 10 100 > 009
./gen.exe 1000 10 100 > 010
./gen.exe 1 100000 100000 > 011
./gen.exe 2 100000 100000 > 012
./gen2.exe 1 100 100 > 013
./gen2.exe 10 100 100 > 014
./gen2.exe 100 100 100 > 015
./gen2.exe 1000 100 100 > 016
./gen2.exe 1 10000 10000 > 017
./gen2.exe 10 10000 10000 > 018
./gen2.exe 100 10000 10000 > 019
./gen2.exe 1 100000 100000 0 > 020
./gen2.exe 1 100000 100000 1 > 021


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
