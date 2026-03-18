import sys
s=sys.stdin.readlines()
s=[e.strip() for e in s]
i=0
ans=-1
while i+1<len(s):
    w=s[i].split(",")[0]
    if s[i]!=f"{w}, {w} {w}ity {w}":
        i+=1
        continue
    if s[i+1]!=f"i said {w}, {w} {w}ity {w}":
        i+=1
        continue
    j=i+2
    while j+1<len(s):
        if s[j]!=f"{w}, {w} {w}ity {w}":
            break
        if s[j+1]!=f"i said {w}, {w} {w}ity {w}":
            break
        j+=2
    ans=max(ans,(j-i)//2*(len(w)*8+23))
    i=j
print(ans)