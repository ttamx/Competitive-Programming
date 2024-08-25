t=int(input())
for i in range(t):
    n=int(input())
    for j in range(n):
        print(sum([*map(int,input().split())]))