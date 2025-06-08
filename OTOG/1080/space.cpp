#include <bits/stdc++.h>
using namespace std;

const int INF=INT_MAX/2;

int goToSpace(int n,int m,int k,vector<pair<int,int>> v){
    int ans=INF;
    vector<vector<int>> a(n+1,vector<int>(m+1));
    for(auto [i,j]:v)a[i][j]++;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
    auto calc=[&](int l,int r,int i,int j){
        return a[r][j]-a[r][i-1]-a[l-1][j]+a[l-1][i-1];
    };
    vector<int> pre(m+1,INF),suf(m+1,INF),top(n+1,INF),bot(n+1,INF);
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            int p=1;
            for(int i=1;i<=m;i++){
                while(calc(l,r,p,i)>=k)p++;
                if(p>1&&calc(l,r,p-1,i)==k){
                    int cur=(i-p+2)*(r-l+1);
                    pre[i]=min(pre[i],cur);
                    suf[p-1]=min(suf[p-1],cur);
                    top[r]=min(top[r],cur);
                    bot[l]=min(bot[l],cur);
                }
            }
        }
    }
    for(int i=2;i<=m;i++)pre[i]=min(pre[i],pre[i-1]);
    for(int i=m-2;i>=1;i--)suf[i]=min(suf[i],suf[i+1]);
    for(int i=2;i<=n;i++)top[i]=min(top[i],top[i-1]);
    for(int i=n-2;i>=1;i--)bot[i]=min(bot[i],bot[i+1]);
    for(int i=1;i<m;i++)ans=min(ans,pre[i]+suf[i+1]);
    for(int i=1;i<n;i++)ans=min(ans,top[i]+bot[i+1]);
    return ans<INF?ans:-1;
}
