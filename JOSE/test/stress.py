import os

os.system("g++ ../sol.cpp -o sol.exe")
os.system("g++ ../ans.cpp -o ans.exe")
os.system("g++ ../gen.cpp -o gen.exe")

index = 0

while True:
    index += 1
    print(f"Generating testcase #{index}")
    os.system("gen.exe > input.txt")
    os.system("sol.exe < input.txt > output_sol.txt")
    os.system("ans.exe < input.txt > output_ans.txt")
    if os.system("FC output_sol.txt output_ans.txt"):
        print("WRONG ANSWER")
        break
    print("OK")