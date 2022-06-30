#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ gen_max.cc -lm -o gen_max.exe -O2 -static --std=c++0x || exit 1
g++ gen_rand.cc -lm -o gen_rand.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 1 100 100 > 002
./gen.exe 2 100 100 > 003
./gen.exe 3 100 100 > 004
./gen.exe 10 100 100 > 005
./gen.exe 11 4 9 > 006
./gen.exe 12 5 10 > 007
./gen.exe 13 6 11 > 008
./gen.exe 14 7 12 > 009
./gen.exe 15 8 13 > 010
./gen.exe 20 100 100 > 011
./gen.exe 30 100 100 > 012
./gen.exe 40 100 100 > 013
./gen.exe 41 100 100 > 014
./gen.exe 42 100 100 > 015
./gen.exe 10 10 20 > 016
./gen.exe 9 9 15 > 017
./gen_max.exe 42 > 018
./gen_max.exe 40 > 019
./gen_max.exe 35 > 020
./gen_max.exe 30 > 021
./gen_max.exe 25 > 022
./gen_max.exe 20 > 023
./gen_rand.exe 10 10 10 > 024
./gen_rand.exe 10 1 1 > 025
./gen_rand.exe 10 2 3 > 026
./gen_rand.exe 42 5 10 > 027
./gen_rand.exe 42 10 20 > 028
./gen_rand.exe 42 20 30 > 029
./gen_rand.exe 42 30 40 > 030
./gen_max.exe 50 > 031
./gen_max.exe 49 > 032
./gen_max.exe 48 > 033
./gen_rand.exe 49 20 30 > 034
./gen_rand.exe 49 30 40 > 035
./gen.exe 49 100 100 0 > 036
./gen.exe 49 100 100 1 > 037
./gen_rand.exe 50 20 30 > 038
./gen_rand.exe 50 30 40 > 039
./gen.exe 50 100 100 0 > 040
./gen.exe 50 100 100 1 > 041


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
