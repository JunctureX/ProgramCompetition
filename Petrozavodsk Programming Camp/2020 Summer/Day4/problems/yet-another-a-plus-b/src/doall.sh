#!/bin/sh

gcc cptest.c -o cptest.exe || exit 1
g++ validator.cpp -lm -o validator.exe -O2 -static --std=c++0x || exit 1
gcc std.c -lm -o std.exe -O2 || exit 1

./cptest.exe < 01.hand > 001
./cptest.exe < 02.hand > 002



mkdir ../tests
for i in ???;do
echo Validating $i
./validator.exe <$i || exit 1
echo Generating $i.a
./std.exe <$i >../tests/$i.a || exit 1
mv $i ../tests/$i
done
rm *.exe
rm *.class
