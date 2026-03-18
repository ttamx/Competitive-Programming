ans=0

with open("input.txt") as f:
    for w in f.readlines():
        dp=[-1000000000000]*13
        dp[0]=0
        for e in w.strip()[::-1]:
            for i in range(12,0,-1):
                dp[i]=max(dp[i],dp[i-1]+int(e)*10**(i-1))
        ans+=dp[12]

print(ans)