ans=0

with open("input.txt") as f:
    for w in f.readline().split(","):
        l,r=map(int,w.split("-"))
        for i in range(l,r+1):
            s=str(i)
            w=len(s)
            if w%2==0 and s[:w//2]==s[w//2:]:
                ans+=i
print(ans)