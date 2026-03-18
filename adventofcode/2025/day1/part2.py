ans=0
pos=50
with open("input.txt") as f:
    for e in f.readlines():
        new_pos=pos
        v=int(e[1:])
        if e[0]=='L':
            new_pos-=v
            if new_pos<=0:
                ans+=(-new_pos)//100+(pos>0)
        else:
            new_pos+=v
            ans+=new_pos//100
        pos=new_pos%100
print(ans)