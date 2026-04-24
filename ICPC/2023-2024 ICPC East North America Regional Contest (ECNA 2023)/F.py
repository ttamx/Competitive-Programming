n=int(input())
a=[*map(int,input().split())]
s=[]
for x in a:
    while len(s)>0 and s[-1]<x:
        s.pop()
    while len(s)>0 and s[-1]==x:
        s.pop()
        x*=2
    s.append(x)
print(max(s))