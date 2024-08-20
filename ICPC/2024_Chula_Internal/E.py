t=int(input())
for _ in range(t):
    n,a=map(int,input().split())
    print(max(n*a,n*(n+1)//2))