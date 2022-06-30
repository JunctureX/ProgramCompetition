#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001
./cptest.exe < 02.hand > 002
./cptest.exe < 03.hand > 003
./cptest.exe < 19.hand > 019
./cptest.exe < 20.hand > 020
./cptest.exe < 21.hand > 021

./gen.exe 1 10 1 10 0 > 004
./gen.exe 1 10 1 10 1 > 005
./gen.exe 3242343 34242344 2 2 > 006
./gen.exe 1000000000 1000000000 100000 1000000 0 > 007
./gen.exe 1000000000 1000000000 100000 1000000 1 > 008
./gen.exe 1000000000 1000000000 1000000 1000000 0 > 009
./gen.exe 1000000000 1000000000 1000000 1000000 1 > 010
./gen.exe 1000000000 1000000000 1000000 1000000 2 > 011
./gen.exe 10000000000 100000000000 1000000 1000000 > 012
./gen.exe 100000000000 1000000000000 1000000 1000000 > 013
./gen.exe 100000000000000000 1000000000000000000 1000000 1000000 0 > 014
./gen.exe 100000000000000000 1000000000000000000 1000000 1000000 1 > 015
./gen.exe 100000000000000000 1000000000000000000 1000000 1000000 2 > 016
./gen.exe 100000000000000000 1000000000000000000 1000000 1000000 3 > 017
./gen.exe 1000000000000000000 1000000000000000000 1000 1000000 > 018


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
