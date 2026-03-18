ans=0
sheet=[80,68,62,57,53,50,48,46,44,42]
mult=[4,3,2]
def score(p):
    if p<1 or p>50: return 0
    if p>10:return 51-p
    return sheet[p-1]
for mul in mult:
    n=int(input())
    r=[100,100]
    mx=0
    for _ in range(n):
        a,b=map(int,input().split()[1:])
        mx=max(mx,a)
        r.append(b)
    r.sort()
    ans+=mul*(mx*10+score(r[0])*2+score(r[1])+score(r[2]))
print(ans)