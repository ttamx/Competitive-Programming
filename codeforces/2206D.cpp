#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct StaticTopTree{
    using P = pair<int,int>;
    int n;
    vector<vector<int>> &adj;
    vector<int> hv,lch,rch,par,type;
    StaticTopTree(vector<vector<int>> &adj):adj(adj){
        n=adj.size();
        hv=lch=rch=par=type=vector<int>(n,-1);
        dfs(0);
        compress(0);
    }
    int dfs(int u){
        int s=1,mx=0;
        for(auto v:adj[u]){
            int t=dfs(v);
            if(t>mx)mx=t,hv[u]=v;
            s+=t;
        }
        return s;
    }
    int add(int l,int r,int t){
        lch.emplace_back(l);
        rch.emplace_back(r);
        par.emplace_back(-1);
        type.emplace_back(t);
        par[l]=par[r]=n;
        return n++;
    }
    P merge(vector<P> a,int t){
        if(a.size()==1)return a[0];
        int tot=0;
        for(auto [i,s]:a)tot+=s;
        vector<P> b,c;
        for(auto [i,s]:a){
            (tot>s?b:c).emplace_back(i,s);
            tot-=s*2;
        }
        auto [i,si]=merge(b,t);
        auto [j,sj]=merge(c,t);
        return {add(i,j,t),si+sj};
    }
    P compress(int i){
        vector<P> a{P(i,1)};
        for(;hv[i]!=-1;i=hv[i])a.emplace_back(rake(i));
        return merge(a,1);
    }
    P rake(int i){
        vector<P> a{P(hv[i],1)};
        for(auto j:adj[i])if(j!=hv[i])a.emplace_back(compress(j));
        return merge(a,0);
    }
};

struct Info{
    ll sum,mx;
};

Info vertex(ll v){
    return Info{0,v};
}

Info compress(Info l,Info r){
    return Info{l.sum+r.sum,max(l.mx,l.sum+r.mx)};
}

Info rake(Info l,Info r){
    return Info{l.sum+r.mx,l.mx+r.mx};
}

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    StaticTopTree t(adj);
    vector<Info> dp(2*n-1);
    auto update=[&](int i){
        dp[i]=(t.type[i]?compress:rake)(dp[t.lch[i]],dp[t.rch[i]]);
    };
    for(int i=0;i<n;i++)dp[i]=vertex(a[i]);
    for(int i=n;i<2*n-1;i++)update(i);
    cout << dp.back().mx << "\n";
    while(q--){
        int u,x;
        cin >> u >> x;
        u--;
        dp[u]=vertex(x);
        while(t.par[u]!=-1)update(u=t.par[u]);
        cout << dp.back().mx << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}