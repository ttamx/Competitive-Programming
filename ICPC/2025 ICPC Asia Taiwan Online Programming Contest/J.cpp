#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

using ll = long long;

int n,k;
vector<pair<int,int>> adj[N];

pair<int,ll> dfs(int u,int p,ll lim){
    int cnt=0;
    ll mx=0,mx2=0;
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        auto [c,d]=dfs(v,u,lim);
        d+=w;
        if(d>lim){
            c++;
            d=w;
        }
        cnt+=c;
        mx2=max(mx2,d);
        if(mx2>mx)swap(mx,mx2);
    }
    if(mx+mx2>lim){
        cnt++;
        mx=0;
    }
    return {cnt,mx};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    ll l=0,r=0;
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
        l=max(l,(ll)w);
        r+=w;
    }
    while(l<r){
        ll m=(l+r)/2;
        if(dfs(1,0,m).first<=k)r=m;
        else l=m+1;
    }
    cout << l << "\n";
}