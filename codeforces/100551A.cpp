#include<bits/stdc++.h>

using namespace std;

const int N=300005;
const int K=1<<20;

int n,q,ct;
map<pair<int,int>,int> mp;
vector<tuple<int,int,int,int>> qr;
vector<pair<int,int>> t[K];
int ans[N];

struct DSU{
    int p[N],sz[N];
    int cnt;
    stack<pair<int,int>> s;
    void init(){
        for(int i=1;i<=n;i++)p[i]=i,sz[i]=1;
        cnt=n;
    }
    int fp(int u){return p[u]==u?u:fp(p[u]);}
    void uni(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return void(s.emplace(0,0));
        if(sz[u]<sz[v])swap(u,v);
        p[v]=u;
        sz[u]+=sz[v];
        s.emplace(u,v);
        cnt--;
    }
    void undo(){
        auto [u,v]=s.top();
        s.pop();
        if(!u)return;
        p[v]=v;
        sz[u]-=sz[v];
        cnt++;
    }
}dsu;

void insert(int l,int r,int i,int x,int y,int u,int v){
    if(y<l||r<x)return;
    if(x<=l&&r<=y)return void(t[i].emplace_back(u,v));
    int m=(l+r)/2;
    insert(l,m,i*2,x,y,u,v);
    insert(m+1,r,i*2+1,x,y,u,v);
}

void solve(int l,int r,int i){
    for(auto [u,v]:t[i])dsu.uni(u,v);
    if(l==r)ans[l]=dsu.cnt;
    else{
        int m=(l+r)/2;
        solve(l,m,i*2);
        solve(m+1,r,i*2+1);
    }
    for(auto _:t[i])dsu.undo();
}

int main(){
    ifstream fin("connect.in");
    ofstream fout("connect.out");
    fin >> n >> q;
    dsu.init();
    for(int i=1;i<=q;i++){
        char c;
        fin >> c;
        if(c=='?')ct++;
        else{
            int u,v;
            fin >> u >> v;
            auto x=minmax(u,v);
            if(c=='+')mp[x]=ct;
            else{
                qr.emplace_back(mp[x]+1,ct,u,v);
                mp.erase(x);
            }
        }
    }
    if(ct==0)exit(0);
    for(auto [e,t]:mp)qr.emplace_back(t+1,ct,e.first,e.second);
    for(auto [l,r,u,v]:qr)if(l<=r)insert(1,ct,1,l,r,u,v);
    solve(1,ct,1);
    for(int i=1;i<=ct;i++)fout << ans[i] << "\n";
}