#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> in(m);
    vector<int> q(m);
    for(auto &[u,v]:in)cin >> u >> v,u--,v--;
    reverse(q.begin(),q.end());
    for(auto &x:q)cin >> x,x--;
    reverse(q.begin(),q.end());
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        if(u==p[u])return u;
        return p[u]=fp(p[u]);
    };
    vector<int> ans;
    for(auto x:q){
        ans.push_back(n);
        auto [u,v]=in[x];
        u=fp(u),v=fp(v);
        if(u!=v){
            p[u]=v;
            n--;
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << '\n';
}