for _ in range(int(input())):
    s=input().strip()
    ok=True
    c=0
    a=0
    l=0
    i=0
    o=0
    for x in s:
        if x in "CUN":
            c+=1
        elif x=='A':
            a+=1
        elif x=='L':
            l+=1
        elif x in "IH":
            i+=1
        elif x=='O':
            o+=1
        else:
            ok=False
            break
    if ok:
        print(max((c+1)//2,a,l,i,o))
    else:
        print(-1)