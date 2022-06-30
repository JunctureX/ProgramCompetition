#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ gen_all.cc -lm -o gen_all.exe -O2 -static --std=c++0x || exit 1
g++ gen_small_n.cc -lm -o gen_small_n.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen_all.exe 1 > 002
./gen_all.exe 2 > 003
./gen_all.exe 3 > 004
./gen_all.exe 4 > 005
./gen_all.exe 5 > 006
./gen_all.exe 6 > 007
./gen_all.exe 7 > 008
./gen_small_n.exe 10 1 1024 > 009
./gen_small_n.exe 20 10000 10000 > 010
./gen_small_n.exe 20 90000 90000 > 011
./gen_small_n.exe 20 1000000 1000000 > 012
./gen_small_n.exe 30 100 1000 > 013
./gen_small_n.exe 50 100 1000 > 014
./gen_small_n.exe 60 100 1000 > 015
./gen.exe 30 60 100000 100000 > 016
./gen.exe 100 200 1000 10000 > 017
./gen.exe 1 1000000000 10000 100000 > 018
./gen.exe 10000000000 100000000000 100000 1000000 0 > 019
./gen.exe 10000000000 100000000000 100000 1000000 1 > 020
./gen.exe 10000000000 100000000000 100000 1000000 2 > 021
./gen.exe 999999999999999999 1000000000000000000 1000000 1000000 0 > 022
./gen.exe 999999999999999999 1000000000000000000 1000000 1000000 1 > 023
./gen.exe 100000000000000000 1000000000000000000 1000000 1000000 0 > 024
./gen.exe 100000000000000000 1000000000000000000 1000000 1000000 1 > 025


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
