#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ gen.cc -lm -o gen.exe -O2 -static --std=c++0x || exit 1
g++ validator.cc -lm -o validator.exe -O2 -static --std=c++0x || exit 1
g++ sol.cc -lm -o sol.exe -O2 -static --std=c++0x || exit 1

./cptest.exe < 01.hand > 001

./gen.exe 1 1 1000 3000 > 002
./gen.exe 1 10 1000 3000 > 003
./gen.exe 1 10 1 300000 > 004
./gen.exe 1 10 300000 300000 > 005
./gen.exe 1 1 300000 300000 > 006
./gen.exe 10 50 1 300000 > 007
./gen.exe 10 50 1 50 > 008
./gen.exe 10 50 30000 300000 > 009
./gen.exe 100 200 30000 300000 0 > 010
./gen.exe 100 200 30000 300000 1 > 011
./gen.exe 100 200 30000 300000 2 > 012
./gen.exe 100 200 30000 300000 3 > 013
./gen.exe 500 500 300000 300000 0 > 014
./gen.exe 500 500 300000 300000 1 > 015
./gen.exe 500 500 300000 300000 2 > 016
./gen.exe 500 500 300000 300000 3 > 017


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
