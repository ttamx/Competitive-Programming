t=int(input())
for _ in range(t):
    n=int(input())
    ans=0
    if n%2==1:
        ans+=n//2+1
        n-=1
    n//=2
    ans+=n*(n+1);
    print(ans)