#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;

struct fenwick{
    ll t[N];
    void init(int n){
        for(int i=1;i<=n;i++)t[i]=0;
    }
    void add(int i,ll v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

void runcase(){
    int q;
    cin >> q;
    vector<tuple<int,int,int>> qr(q);
    vector<vector<int>> adj(3);
    int n=1;
    for(auto &[t,x,y]:qr){
        cin >> t;
        if(t==1){
            cin >> x;
            adj[x].emplace_back(++n);
            adj.emplace_back(vector<int>(0));
        }else{
            cin >> x >> y;
        }
    }
    f.init(n);
    vector<int> tin(n+2),tout(n+2);
    int timer=0;
    function<void(int)> dfs=[&](int u){
        tin[u]=++timer;
        for(auto v:adj[u])dfs(v);
        tout[u]=timer;
    };
    dfs(1);
    n=1;
    ll ans=0;
    for(auto [t,x,y]:qr){
        if(t==1){
            f.add(tin[++n],-f.read(tin[x]));
            f.add(tout[n]+1,f.read(tin[x]));
        }else{
            f.add(tin[x],y);
            f.add(tout[x]+1,-y);
        }
    }
    for(int i=1;i<=n;i++)cout << f.read(tin[i]) << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}