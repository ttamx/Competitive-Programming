n=int(input())
d=dict()
d['S']=0
d['M']=0
d['L']=0
for _ in range(n):
    a,b=input().split()
    d[a]+=int(b)
print((d['S']+5)//6+(d['M']+7)//8+(d['L']+11)//12)