ans=0

with open("input.txt") as f:
    a=[]
    phase=0
    for e in f.readlines():
        if phase==0:
            if len(e.strip())==0:
                phase=1
                continue
            l,r=map(int,e.split("-"))
            a.append((l,0,+1))
            a.append((r+1,0,-1))
        else:
            x=int(e)
            a.append((x,1,0))
    a.sort()

    bal=0
    ans=0
    for x,t,v in a:
        bal+=v
        if t and bal>0:
            ans+=1

print(ans)