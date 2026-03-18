n=int(input())
a1,b1=map(int,input().split())
a=[[*map(int,input().split())]for _ in " "*n]
a.sort(key=lambda x:x[0]*x[1])
ans=a1//b1
prod=a1
for e in a:
 ans=max(ans,prod//e[1])
 prod*=e[0]
print(ans)