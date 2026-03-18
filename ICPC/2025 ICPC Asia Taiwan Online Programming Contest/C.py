import sys
input=sys.stdin.readline
for _ in range(int(input())):
    n,m=map(int,input().split())
    a=[0]*n
    for i in range(m):
        x,y,v=map(int,input().split())
        x-=1
        y-=1
        a[x]+=v
        a[y]+=v
        a[x],a[y]=a[y],a[x]
    print(max(a))