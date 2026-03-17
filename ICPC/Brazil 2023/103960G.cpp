#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = complex<ll>;

ll cross(P a,P b){
    return imag(conj(a)*b);
}

ll cross(P a,P b,P o){
    return cross(a-o,b-o);
}

P get(){
    ll x,y;
    cin >> x >> y;
    return P(x,y);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<vector<int>> adj(n);
    map<pair<P,P>,vector<int>> mp;
    for(int i=0;i<n;i++){
        vector<P> p(3);
        for(auto &x:p){
            x=get();
        }
        for(int j=0;j<3;j++){
            int k=(j+1)%3;
            mp[minmax(p[j],p[k])].emplace_back(i);
        }
        a[i]=abs(cross(p[0],p[1],p[2]));
    }
    for(auto &[_,e]:mp){
        if(e.size()==2){
            int u=e[0],v=e[1];
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
    }
    function<pair<ll,ll>(int,int)> dfs=[&](int u,int p){
        pair<ll,ll> res(0,0);
        ll mx=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            auto [v1,v2]=dfs(v,u);
            res.first+=max(v1,v2);
            mx=max(mx,v1+a[u]+a[v]-max(v1,v2));
        }
        res.second=res.first+mx;
        return res;
    };
    auto [v1,v2]=dfs(0,-1);
    cout << fixed << setprecision(1) << max(v1,v2)/2.0 << "\n";
}