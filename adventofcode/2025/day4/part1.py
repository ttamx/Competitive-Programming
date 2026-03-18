ans=0

with open("input.txt") as f:
    g=[e.strip() for e in f.readlines()]
    n=len(g)
    m=len(g[0])
    c=[list([0]*m) for _ in range(n)]
    for i in range(n):
        for j in range(m):
            if g[i][j]!='@':
                continue
            for di in range(-1,2):
                for dj in range(-1,2):
                    ii=i+di
                    jj=j+dj
                    if ii<0 or ii>=n or jj<0 or jj>=m or g[ii][jj]!='@':
                        continue
                    c[i][j]+=1
            c[i][j]-=1
            if c[i][j]<4:
                ans+=1

print(ans)