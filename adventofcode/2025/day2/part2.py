ans=0

with open("input.txt") as f:
    for w in f.readline().split(","):
        l,r=map(int,w.split("-"))
        for i in range(l,r+1):
            s=str(i)
            w=len(s)
            for t in range(1,w):
                if w%t>0:continue
                ok=True
                for j in range(0,w,t):
                    if s[:t]!=s[j:j+t]:
                        ok=False
                        break
                if ok:
                    ans+=i
                    break
                        
print(ans)