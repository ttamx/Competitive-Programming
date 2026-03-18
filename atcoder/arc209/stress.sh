#!/bin/bash
# write a stress test for comparing output of to solutions

# create variables for the two solutions
GENERATOR="./D_gen.cpp"
SOLUTION1="./D_brute.cpp"
SOLUTION2="./D_A_A_i.cpp"

# compile the generator and solutions
g++ -o generator $GENERATOR
g++ -o solution1 $SOLUTION1
g++ -o solution2 $SOLUTION2

# number of test cases
TESTS=1000
for ((i=1; i<=TESTS; i++)); do
    echo "Test case #$i"
    # generate a test case
    ./generator > input.txt
    # get outputs from both solutions
    ./solution1 < input.txt > output1.txt
    ./solution2 < input.txt > output2.txt
    # compare outputs
    if ! diff output1.txt output2.txt; then
        echo "Mismatch found on test case #$i"
        echo "Input:"
        cat input.txt
        echo "Output from solution1:"
        cat output1.txt
        echo "Output from solution2:"
        cat output2.txt
        exit 1
    else
        echo "Outputs match for test case #$i"
    fi
done
echo "All $TESTS test cases passed!"