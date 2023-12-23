#include<bits/stdc++.h>

using namespace std;

struct DSU{
    vector<int> p,sz;
    DSU(int n=0){
        init(n+1);
    }
    void init(int n){
        p.resize(n);
        iota(p.begin(),p.end(),0);
        sz.assign(n,1);
    }
    int fp(int u){
        return p[u]=(u==p[u]?u:fp(p[u]));
    }
    bool same(int u,int v){
        return fp(u)==fp(v);
    }
    bool merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        sz[u]+=sz[v];
        p[v]=u;
        return true;
    }
    int size(int u){
        return sz[fp(u)];
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    DSU dsu1(n),dsu2(n);
    vector<int> pa(n,-1);
    int ans=0;
    auto reroot=[&](int st){
        for(int u=st,v=-1;u!=-1;){
            u=dsu2.fp(u);
            int p=pa[u];
            pa[u]=v,v=u,u=p;
        }
    };
    vector<bool> vis(n);
    auto compress=[&](int u,int v){
        int lca=-1;
        int u2=u,v2=v;
        vector<int> a,b;
        while(u!=-1||v!=-1){
            if(u!=-1){
                u=dsu2.fp(u);
                if(vis[u]){
                    lca=u;
                    break;
                }
                vis[u]=true;
                a.emplace_back(u);
                u=pa[u];
            }
            swap(u,v),swap(a,b);
        }
        for(auto x:a){
            if(x==lca)break;
            dsu2.p[x]=lca;
            ans--;
        }
        for(auto x:b){
            if(x==lca)break;
            dsu2.p[x]=lca;
            ans--;
        }
        for(auto x:a)vis[x]=false;
        for(auto x:b)vis[x]=false;
    };
    while(m--){
        int u,v;
        cin >> u >> v;
        u=dsu2.fp(u),v=dsu2.fp(v);
        if(!dsu2.same(u,v)){
            int u2=dsu1.fp(u),v2=dsu1.fp(v);
            if(u2!=v2){
                ans++;
                if(dsu1.sz[u2]>dsu1.sz[v2])swap(u,v),swap(u2,v2);
                dsu1.merge(u2,v2);
                reroot(v);
                pa[v]=u;
            }else{
                compress(u,v);
            }
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}