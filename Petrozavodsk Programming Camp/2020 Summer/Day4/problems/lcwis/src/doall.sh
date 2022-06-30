#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen_rand.cc -lm -o gen_rand.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen_rand.exe 1 10 > 002
./gen_rand.exe 10 10 > 003
./gen_rand.exe 10 20 > 004
./gen_rand.exe 20 20 > 005
./gen_rand.exe 50 100 > 006
./gen_rand.exe 100 100 > 007
./gen_rand.exe 1000 1000 > 008
./gen_rand.exe 10000 10000 > 009
./gen_rand.exe 100000 100000 > 010
./gen_rand.exe 1000000 1000000 0 > 011
./gen_rand.exe 1000000 1000000 1 > 012
./gen_rand.exe 1000000 1000000 2 > 013
./gen_rand.exe 1000000 1000000 3 > 014
./gen_rand.exe 1000000 1000000 4 > 015


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
