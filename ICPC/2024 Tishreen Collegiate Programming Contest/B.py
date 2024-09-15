t=int(input())
for _ in range(t):
    s=input()
    n=len(s)
    ans=0
    for i in range(n//2):
        ans+=abs(ord(s[i])-ord(s[n-i-1]))
    print(ans)