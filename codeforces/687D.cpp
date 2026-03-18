#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int M=1e6+5;
const int K=1<<21;

int n,m,q;

struct Edge{
    int u,v,w;
    bool operator<(const Edge &o)const{
        return w>o.w;
    }
}edges[M];

struct DSU{
    bool ans;
    int fa[N],sz[N],col[N];
    stack<pair<int,int>> st;
    void init(){
        ans=true;
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
            col[i]=0;
        }
    }
    pair<int,int> find(int u){
        if(u==fa[u])return {u,col[u]};
        auto res=find(fa[u]);
        res.second^=col[u];
        return res;
    }
    bool merge(int u,int v){
        auto [pu,cu]=find(u);
        auto [pv,cv]=find(v);
        if(pu==pv){
            if(cu==cv)ans=false;
            return false;
        }
        if(sz[pu]<sz[pv])swap(pu,pv);
        if(cu==(cv^col[pu]))col[pv]^=1;
        fa[pv]=pu;
        sz[pu]+=sz[pv];
        st.emplace(pu,pv);
        return true;
    }
    void reset(){
        while(!st.empty()){
            auto [u,v]=st.top();
            st.pop();
            sz[u]-=sz[v];
            fa[v]=v;
        }
        ans=true;
    }
}dsu;

struct Info{
    vector<int> all,good;
    friend Info operator+(const Info &l,const Info &r){
        Info res;
        for(int i=0,j=0;i<l.all.size()||j<r.all.size();){
            if(j==r.all.size()||(i<l.all.size()&&edges[l.all[i]]<edges[r.all[j]])){
                res.all.emplace_back(l.all[i++]);
            }else{
                res.all.emplace_back(r.all[j++]);
            }
        }
        for(auto i:res.all){
            if(dsu.merge(edges[i].u,edges[i].v)){
                res.good.emplace_back(i);
            }else if(!dsu.ans){
                res.good.emplace_back(i);
                break;
            }
        }
        dsu.reset();
        return res;
    }
};

struct Segtree{
    Info t[K];
    void build(int l,int r,int i){
        if(l==r){
            t[i].all=t[i].good={l};
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void query(int l,int r,int i,int x,int y,vector<int> &e){
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            e.insert(e.end(),t[i].good.begin(),t[i].good.end());
            return;
        }
        int m=(l+r)/2;
        query(l,m,i*2,x,y,e);
        query(m+1,r,i*2+1,x,y,e);
    }
}seg;


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    dsu.init();
    seg.build(1,m,1);
    while(q--){
        int l,r;
        cin >> l >> r;
        vector<int> tmp;
        seg.query(1,m,1,l,r,tmp);
        sort(tmp.begin(),tmp.end(),[&](int i,int j){
            return edges[i]<edges[j];
        });
        int ans=-1;
        for(auto i:tmp){
            dsu.merge(edges[i].u,edges[i].v);
            if(!dsu.ans){
                ans=edges[i].w;
                break;
            }
        }
        dsu.reset();
        cout << ans << "\n";
    }
}