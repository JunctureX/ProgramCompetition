#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 2 10 0 > 002
./gen.exe 2 10 1 > 003
./gen.exe 10 20 0 > 004
./gen.exe 10 20 1 > 005
./gen.exe 10 20 2 > 006
./gen.exe 10 20 3 > 007
./gen.exe 10 20 4 > 008
./gen.exe 10 20 5 > 009
./gen.exe 10 20 6 > 010
./gen.exe 10 20 8 > 011
./gen.exe 100 200 0 > 012
./gen.exe 100 200 1 > 013
./gen.exe 100 200 2 > 014
./gen.exe 100 200 3 > 015
./gen.exe 100 200 4 > 016
./gen.exe 100 200 5 > 017
./gen.exe 100 200 6 > 018
./gen.exe 100 200 7 > 019
./gen.exe 100 200 8 > 020
./gen.exe 50000 50000 0 > 021
./gen.exe 50000 50000 1 > 022
./gen.exe 50000 50000 2 > 023
./gen.exe 50000 50000 3 > 024
./gen.exe 50000 50000 4 > 025
./gen.exe 50000 50000 5 > 026
./gen.exe 50000 50000 6 > 027
./gen.exe 50000 50000 7 > 028
./gen.exe 50000 50000 8 > 029
./gen.exe 100000 100000 9 0 > 030
./gen.exe 100000 100000 9 1 > 031
./gen.exe 100000 100000 9 2 > 032
./gen.exe 200000 200000 0 > 033
./gen.exe 200000 200000 1 > 034
./gen.exe 200000 200000 2 > 035
./gen.exe 200000 200000 3 > 036
./gen.exe 200000 200000 5 > 037
./gen.exe 200000 200000 9 0 > 038
./gen.exe 200000 200000 9 1 > 039
./gen.exe 200000 200000 9 2 > 040


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
