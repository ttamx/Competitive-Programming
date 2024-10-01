t=input()
for _ in range(int(input())):
    s=input()
    ans=100
    for i in range(len(t)):
        p=0
        res=0
        for c in t[i:]:
            if c==s[p]:
                p+=1
                if p==len(s):
                    ans=min(ans,res)
                    break
            else:
                res+=1
    print(-1 if ans==100 else ans)