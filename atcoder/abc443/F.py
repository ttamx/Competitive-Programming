n=int(input())
if n%10==0:
    print(-1)
    exit(0)
if n<10:
    print(n)
    exit(0)
n*=9
ans=n+9
cur=1
while sum(map(int,str(ans)))>9:
    print(ans)
    ans+=n
print(ans//9-1)