#include<bits/stdc++.h>

using namespace std;

const int N=50005;
const int M=1e5+5;
const int Q=1e5+5;
const int K=1000;

int n,m,q;
int ans[Q];
bool used[M];

struct Edge{
    int u,v,w;
    bool operator<(const Edge &o)const{
        if(w!=o.w)return w>o.w;
        if(u!=o.u)return u<o.u;
        return v<o.v;
    }
}ed[M];
multiset<Edge> ms;

struct Query{
    int t,s,w;
    bool operator<(const Query &o)const{
        return w>o.w;
    }
}qr[Q];

struct DSU{
    int p[N],sz[N];
    stack<pair<int,int>> s;
    void init(){
        for(int i=1;i<=n;i++)p[i]=i,sz[i]=1;
        while(!s.empty())s.pop();
    }
    int fp(int u){
        return p[u]==u?u:fp(p[u]);
    }
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        if(sz[u]<sz[v])swap(u,v);
        p[v]=u;
        sz[u]+=sz[v];
        s.emplace(u,v);
        return true;
    }
    int state(){
        return s.size();
    }
    void undo(int t){
        while(s.size()>t){
            auto [u,v]=s.top();
            s.pop();
            p[v]=v;
            sz[u]-=sz[v];
        }
    }
    int size(int u){
        return sz[fp(u)];
    }
}dsu;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        cin >> ed[i].u >> ed[i].v >> ed[i].w;
        ms.emplace(ed[i]);
    }
    cin >> q;
    for(int i=1;i<=q;i++)cin >> qr[i].t >> qr[i].s >> qr[i].w;
    for(int l=1,r=K;l<=q;l+=K,r+=K){
        r=min(r,q);
        dsu.init();
        vector<int> upd;
        for(int i=l;i<=r;i++){
            int id=qr[i].s;
            if(qr[i].t==1&&!used[id]){
                used[id]=true;
                upd.emplace_back(id);
                ms.erase(ms.find(ed[id]));
            }
        }
        vector<tuple<int,int,vector<int>>> qrs;
        for(int i=l;i<=r;i++){
            if(qr[i].t==1){
                ed[qr[i].s].w=qr[i].w;
            }else{
                vector<int> res;
                for(auto j:upd)if(ed[j].w>=qr[i].w)res.emplace_back(j);
                qrs.emplace_back(qr[i].w,i,res);
            }
        }
        sort(qrs.rbegin(),qrs.rend());
        auto it=ms.begin();
        for(auto [w,i,v]:qrs){
            while(it!=ms.end()&&it->w>=w){
                dsu.uni(it->u,it->v);
                it++;
            }
            int st=dsu.state();
            for(auto j:v)dsu.uni(ed[j].u,ed[j].v);
            ans[i]=dsu.size(qr[i].s);
            dsu.undo(st);
        }
        for(auto i:upd){
            used[i]=false;
            ms.emplace(ed[i]);
        }
    }
    for(int i=1;i<=q;i++)if(qr[i].t==2)cout << ans[i] << "\n";
}