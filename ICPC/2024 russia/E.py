n,x=map(int,input().split())
a=[*map(int,input().split())]
tot=0
a.sort()
for i,e in enumerate(a[::-1]):
    tot+=e/(i+1)
if tot-x>=-1e-9:
    print("YES")
else:
    print("NO")