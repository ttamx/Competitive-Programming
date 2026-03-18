ans=0

with open("input.txt") as f:
    g=[e.strip() for e in f.readlines()]
    n=len(g)
    m=len(g[0])
    c=[list([0]*m) for _ in range(n)]
    qu=[]
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
                qu.append((i,j))
    while ans<len(qu):
        i,j=qu[ans]
        ans+=1
        for di in range(-1,2):
            for dj in range(-1,2):
                ii=i+di
                jj=j+dj
                if ii<0 or ii>=n or jj<0 or jj>=m or g[ii][jj]!='@':
                    continue
                c[ii][jj]-=1
                if c[ii][jj]==3:
                    qu.append((ii,jj))

print(ans)