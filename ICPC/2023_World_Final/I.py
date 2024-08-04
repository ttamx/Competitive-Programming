import sys
input=sys.stdin.readline
n,m=[*map(int,input().split())]
tot=0
for i in range(n):
    tot+=sum([*map(int,input().split())])
print(tot/(n*m))