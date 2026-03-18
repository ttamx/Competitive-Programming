ans=0

with open("input.txt") as f:
    for w in f.readlines():
        v=0
        w=w.strip()
        for i in range(len(w)-1):
            v=max(v,int(w[i])*10+max([int(e) for e in w[i+1:]]))
        ans+=v

print(ans)