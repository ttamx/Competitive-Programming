import sys
input=sys.stdin.readline
for _ in range(int(input())):
    s=input()
    n=len(s)
    t=s[::-1]
    dp=[[int(1e9)]*(n+1)]*(n+1)
    for i in range(n+1):
        for j in range(n+1):
            if i+1<=n:
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1)
            if j+1<=n:
                dp[i][j+1]=min(dp[i][j+1],dp[i][j]+1)
            if i+1<=n and j+1<=n:
                dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+(1 if s[i]!=t[j] else 0))
    print(dp[n][n])
