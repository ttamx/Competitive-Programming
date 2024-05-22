#!/bin/bash
genFile="gen.cpp"
solFile="sol.cpp"
outFile="out.cpp"
testCases=1000000
g++ -std=gnu++17 -O2 -o gen ./$genFile
g++ -std=gnu++17 -O2 -o sol ./$solFile
g++ -std=gnu++17 -O2 -o out ./$outFile
for ((i = 1; i <= testCases; i++)); do
  echo "Test case $i"
  ./gen $i >input.txt
  ./sol <input.txt >output1.txt
  ./out <input.txt >output2.txt
  if diff -w output1.txt output2.txt; then
    echo "OK"
    rm -f input.txt output1.txt output2.txt
  else
    echo "Wrong Answer"
    break
  fi
done
rm -f gen sol out