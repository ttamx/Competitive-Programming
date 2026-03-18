ans=0

with open("input.txt") as f:
    a=[e for e in f.readlines()]
    n=len(a)
    m=max(len(e) for e in a)
    b=[]
    for i in range(m-1,-1,-1):
        b.append("")
        for j in range(n-1):
            if i<len(a[j]) and a[j][i].isdigit():
                b[-1]+=a[j][i]
        if b[-1]=="":
            b.pop()
        if i<len(a[-1]) and a[-1][i]=="*":
            res=1
            for e in b:
                res*=int(e)
            ans+=res
            b=[]
        if i<len(a[-1]) and a[-1][i]=="+":
            res=0
            for e in b:
                res+=int(e)
            ans+=res
            b=[]

print(ans)