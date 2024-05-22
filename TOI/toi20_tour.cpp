#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int LIM=INT_MAX/2;
const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,l;
    cin >> n >> m >> l;
    while(l--){
        int x;
        cin >> x;
    }
    vector<vector<pair<int,array<int,2>>>> adj(n);
    while(m--){
        int u,v,s,w;
        cin >> u >> v >> s >> w;
        u--,v--;
        array<int,2> a{0,0};
        a[s-1]=w;
        adj[u].emplace_back(v,a);
    }
    vector<vector<array<ll,2>>> dp(n);
    dp[0].push_back({0,0});
    for(int u=0;u<n;u++){
        for(auto [v,a]:adj[u]){
            for(auto b:dp[u]){
                b[0]+=a[0],b[1]+=a[1];
                dp[v].emplace_back(b);
            }
        }
    }
    auto pt=dp.back();
    sort(pt.begin(),pt.end());
    n=pt.size();
    for(int i=1;i<n;i++)if(pt[i]==pt[i-1])cout << 0,exit(0);
    set<pair<int,int>> s;
    auto sq=[&](ll x){
        return x*x;
    };
    auto fsqrt=[&](ll x){
        int l=0,r=LIM;
        while(l<r){
            int m=(l+r)/2;
            if(sq(m)<x)l=m+1;
            else r=m;
        }
        return l;
    };
    ll ans=INF;
    int dist=LIM;
    for(int i=0,p=0;i<n;i++){
        while(p<i&&pt[i][0]-pt[p][0]>=dist){
            s.erase({pt[p][1],pt[p][0]});
            p++;
        }
        for(auto it=s.upper_bound({pt[i][1]-dist,0});it!=s.end()&&it->first<pt[i][1]+dist;it++){
            ans=min(ans,sq(pt[i][0]-it->second)+sq(pt[i][1]-it->first));
        }
        dist=fsqrt(ans);
        s.emplace(pt[i][1],pt[i][0]);
    }
    cout << ans;
}