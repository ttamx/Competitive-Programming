ans=0

with open("input.txt") as f:
    a=[e.split() for e in f.readlines()]
    n=len(a)
    m=len(a[0])
    for i in range(m):
        if a[-1][i]=="+":
            res=0
            for j in range(n-1):
                res+=int(a[j][i])
            ans+=res
        else:
            res=1
            for j in range(n-1):
                res*=int(a[j][i])
            ans+=res

print(ans)