s=input()
i=0
ans=""
while i<len(s):
    j=i+1
    while j<len(s) and s[i]==s[j]:
        j+=1
    sz=j-i
    if s[i]=='7':
        left=sz%4
        cnt=sz//4
        c='s'
        if left>0:
            ans+=chr(ord(c)-4+left)
        ans+=c*cnt
    elif s[i]=='9':
        left=sz%4
        cnt=sz//4
        c='z'
        if left>0:
            ans+=chr(ord(c)-4+left)
        ans+=c*cnt
    else:
        left=sz%3
        cnt=sz//3
        c=chr(ord('a')+(int(s[i])-1)*3-1)
        if int(s[i])>7:
            c=chr(ord(c)+1)
        if left>0:
            ans+=chr(ord(c)-3+left)
        ans+=c*cnt
    i=j
print(ans)