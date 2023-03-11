#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;
const int inf=1e9;

int n,m,s;
int rt[N],dist[N];
bool vis[N];
vector<int> adj[N];
multiset<int> ms[11][N];

struct segtree{
    int t[K];
    void update(int l,int r,int i,int &x,int &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]+=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(0,n-1,1,x,v);
    }
    int query(int l,int r,int i,int &x,int &y){
        if(y<l||r<x)return -2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(0,n-1,1,x,y);
    }
}sa[11],sl[11],sr[11];

void initialize(int N,int M,int S,vector<vector<int>> R)
{
    n=N,m=M,s=S;
    for(int i=1;i<=10;i++)for(int j=0;j<n;j++)sr[i].update(j,-inf-i*j);
    for(int i=1;i<=10;i++)for(int j=0;j<n;j++)sl[i].update(j,-inf-i*(n-j-1));
    for(int i=1;i<=10;i++)for(int j=0;j<n;j++)sa[i].update(j,-inf);
    for(int i=1;i<=10;i++)for(int j=0;j<n;j++)ms[i][j].emplace(-inf);
    for(auto r:R){
        int u=r[0],v=r[1];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=0;i<=s;i++){
        queue<int> q;
        q.emplace(i);
        vis[i]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            rt[u]=i;
            for(auto v:adj[u]){
                if(vis[v]||v<=s)continue;
                vis[v]=true;
                dist[v]=dist[u]+1;
                q.emplace(v);
            }
        }
    }
}

void panda_spawn(int P,int L,int X)
{
    int val=*prev(ms[L][rt[X]].end());
    sl[L].update(rt[X],-val);
    sr[L].update(rt[X],-val);
    sa[L].update(rt[X],-val);
    ms[L][rt[X]].emplace(P-L*dist[X]);
    val=*prev(ms[L][rt[X]].end());
    sl[L].update(rt[X],val);
    sr[L].update(rt[X],val);
    sa[L].update(rt[X],val);
}

void panda_evac(int P,int L,int X)
{
    int val=*prev(ms[L][rt[X]].end());
    sl[L].update(rt[X],-val);
    sr[L].update(rt[X],-val);
    sa[L].update(rt[X],-val);
    ms[L][rt[X]].erase(ms[L][rt[X]].find(P-L*dist[X]));
    val=*prev(ms[L][rt[X]].end());
    sl[L].update(rt[X],val);
    sr[L].update(rt[X],val);
    sa[L].update(rt[X],val);
}

int travel(int A,int B)
{
    if(A>B)swap(A,B);
    int res=-inf;
    for(int i=1;i<=10;i++)res=max({res,sl[i].query(0,A-1)+i*(n-A-1),sa[i].query(A,B),sr[i].query(B+1,n-1)+i*B});
    return res;
}
