#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

using ll = long long;
using T = tuple<ll,int,int>;
using U = tuple<ll,int,int,int>;

int n,m,q;
int s[N],deg[N];
int rt;
ll cur,ans[N];
vector<T> edge;
priority_queue<T,vector<T>,greater<T>> comp[N];
priority_queue<U,vector<U>,greater<U>> pq;

struct DSU{
    int p[N];
    void init(){
        for(int i=1;i<=n;i++)p[i]=i;
    }
    int fp(int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    }
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        return u!=v?p[u]=v,true:false;
    }
}dsu;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        cin >> s[i];
    }
    rt=min_element(s+1,s+n+1)-s;
    cur+=1LL*(n-2)*s[rt]+*max_element(s+1,s+n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        edge.emplace_back(s[u]+s[v],u,v);
    }
    sort(edge.begin(),edge.end());
    dsu.init();
    for(auto [w,u,v]:edge)if(dsu.uni(u,v)){
        comp[u].emplace(w,u,v);
        comp[v].emplace(w,v,u);
    }
    dsu.init();
    for(int i=1;i<=n;i++)if(!comp[i].empty()){
        auto [w,u,v]=comp[i].top();
        pq.emplace(w-(s[rt]+s[u]),u,v,i);
    }
    int cnt=n-1;
    ans[cnt]=cur;
    while(!pq.empty()){
        auto [w,u,v,p]=pq.top();
        pq.pop();
        u=dsu.fp(u),v=dsu.fp(v);
        if(u==v||u!=p)continue;
        cur+=w;
        ans[--cnt]=cur;
        if(comp[u].size()>comp[v].size())swap(comp[u],comp[v]);
        dsu.p[u]=v;
        while(!comp[u].empty()){
            comp[v].emplace(comp[u].top());
            comp[u].pop();
        }
        while(!comp[v].empty()){
            auto [c,a,b]=comp[v].top();
            if(dsu.fp(a)!=dsu.fp(b))break;
            comp[v].pop();
        }
        if(!comp[v].empty()){
            auto [c,a,b]=comp[v].top();
            pq.emplace(c-(s[rt]+s[v]),a,b,v);
        }
    }
    for(int i=0;i<=q;i++)cout << ans[min(i,n-1)] << "\n";
}