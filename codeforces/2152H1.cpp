#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=250005;

int n,q;
vector<tuple<int,int,int>> edges;
ll a[N],sum[N],dp[N];
int p[N];

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

void runcase(){
    cin >> n;
    edges.resize(n-1);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        a[u]+=w;
        a[v]+=w;
    }
    sort(edges.rbegin(),edges.rend());
    cin >> q;
    while(q--){
        ll t;
        cin >> t;
        for(int i=1;i<=n;i++){
            p[i]=i;
            sum[i]=a[i];
            dp[i]=max(t-sum[i],0LL);
        }
        for(auto [w,u,v]:edges){
            u=fp(u),v=fp(v);
            sum[u]+=sum[v]-2*w;
            dp[u]=max(dp[u]+dp[v],t-sum[u]);
            p[v]=u;
        }
        cout << dp[fp(1)] << "\n";
    }
    for(int i=1;i<=n;i++){
        a[i]=sum[i]=dp[i]=0;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}