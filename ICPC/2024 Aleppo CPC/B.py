t=int(input())
for _ in range(t):
    n,m=map(int,input().split())
    tot=sum([*map(int,input().split())])
    print(9-tot%9)