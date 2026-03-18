ans=0
pos=50
with open("input.txt") as f:
    for e in f.readlines():
        v=int(e[1:])
        if e[0]=='L':
            pos=(pos+100-v)%100
        else:
            pos=(pos+v)%100
        if pos==0:
            ans+=1
print(ans)