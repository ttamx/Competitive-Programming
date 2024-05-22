#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n,m,k;
int p[N],sz[N],dp[N];
int st;
vector<int> comp;

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    int e;
    cin >> e;
    for(int i=1;i<=n;i++)p[i]=i,sz[i]=0;
    for(int i=0;i<e;i++){
        int u,v;
        cin >> u >> v;
        p[fp(u)]=p[v];
    }
    for(int i=1;i<=n;i++)sz[fp(i)]++;
    int st=sz[fp(1)];
    for(int i=1;i<=n;i++)if(fp(i)==fp(1))comp.emplace_back(i);
    for(int g=2;g<=m;g++){
        cin >> e;
        for(int i=1;i<=n;i++)p[i]=i,sz[i]=0;
        for(int i=0;i<e;i++){
            int u,v;
            cin >> u >> v;
            p[fp(u)]=p[v];
        }
        for(int i=1;i<=n;i++)sz[fp(i)]++;
        for(int i=1;i<=n;i++)dp[i]=max(dp[i],sz[fp(i)]);
    }
    int ans=0;
    for(auto i:comp)ans=max(ans,dp[1]);
    cout << ans+st;
}