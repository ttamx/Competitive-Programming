n=int(input())
ans=0
for i in range(1,n-1,2):
    ans+=(n-i)*(n-i-1)//2+1
print(ans)