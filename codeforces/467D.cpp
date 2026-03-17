#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<ll,ll,ll>;

const ll MOD=1e9+7;
const ll BASE=101;

ll n,m;
vector<ll> a;
map<ll,vector<ll>> adj;
map<ll,pair<ll,ll>> dp;
set<ll> vis;
priority_queue<T,vector<T>,greater<T>> pq;

void push(ll cnt,ll len,ll u){
    pair<ll,ll> val(cnt,len);
    if(!dp.count(u)||val<dp[u]){
        dp[u]=val;
        pq.emplace(cnt,len,u);
    }
}

ll read(){
    string s;
    cin >> s;
    ll res=0;
    for(auto &x:s){
        x=tolower(x);
        res=(res*BASE+x-'a'+1)%MOD;
    }
    ll len=s.size();
    ll cnt=count(s.begin(),s.end(),'r');
    push(cnt,len,res);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for(auto &x:a)x=read();
    cin >> m;
    for(ll i=0;i<m;i++){
        ll u=read(),v=read();
        adj[v].emplace_back(u);
    }
    while(!pq.empty()){
        auto [cnt,len,u]=pq.top();
        pq.pop();
        if(!vis.emplace(u).second)continue;
        for(auto v:adj[u]){
            push(cnt,len,v);
        }
    }
    ll ans1=0,ans2=0;
    for(auto x:a){
        auto [v1,v2]=dp[x];
        ans1+=v1,ans2+=v2;
    }
    cout << ans1 << " " << ans2 << "\n";
}