#include "colorful.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> p2;

const int N=5e4+5;
const int K=45;
const int NK=N*K;

int n,m,k,nk,sn;
int prime[K];
bool notprime[3000];
vector<int> rt,lv,pos;
int spos[NK];
vector<array<int,22>> pa;
vector<int> xy[N],adj[NK],rev[NK];
vector<vector<int>> scc,sadj;
int sccid[NK];
stack<int> s;
bool vis[NK];

int calc(int x,int y){
    return x*(k+1)+y;
}

void print(int x){
    cout << "( " << x/(k+1) << ", " << x%k << ") ";
}

void dfs(int u){
    if(vis[u])return;
    vis[u]=true;
    for(auto v:adj[u])dfs(v);
    s.push(u);
}

void kos(int u,int i){
    if(vis[u])return;
    vis[u]=true;
    sccid[u]=i;
    for(auto v:rev[u])kos(v,i);
    scc[i].push_back(u);
}

void sdfs(int u,int p,int r){
    rt[u]=r;
    pa[u][0]=p;
    if(u!=p)lv[u]=lv[p]+1;
    if(lv[u]>1)pos[u]=pos[p];
    for(auto v:sadj[u])sdfs(v,u,r);
}

void init_machine(int N, int M, int K, int Q, vector<int> x, vector<int> y){
    n=N,m=M,k=K,nk=(n+1)*(k+1);
    for(int cnt=0,i=2;cnt<k;i++){
        if(notprime[i])continue;
        prime[cnt++]=i;
        for(int j=i;j<3000;j+=i)notprime[i]=true;
    }
    for(int i=0;i<m;i++){
        int u=x[i],v=y[i];
        xy[u].push_back(v);
        xy[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            p2 mn={2e9,i};
            for(auto v:xy[i])mn=min(mn,{v%prime[j],v});
            int u=calc(i,j);
            int v=calc(mn.second,(j+1)%k);
            adj[u].push_back(v);
            rev[v].push_back(u);
        }
    }
    for(int i=0;i<nk;i++)if(!vis[i])dfs(i);
    for(int i=0;i<nk;i++)vis[i]=false;
    while(!s.empty()){
        int u=s.top();
        s.pop();
        if(vis[u])continue;
        scc.push_back(vector<int>(0));
        sadj.push_back(vector<int>(0));
        kos(u,scc.size()-1);
    }
    sn=scc.size();
    pa.resize(sn);
    rt.resize(sn);
    lv.resize(sn);
    pos.resize(sn);
    for(int i=0;i<sn;i++)for(int j=0;j<scc[i].size();j++){
        int u=scc[i][j];
        spos[u]=j;
        for(auto v:rev[u]){
            if(sccid[v]==i)continue;
            sadj[i].push_back(sccid[v]);
            pos[sccid[v]]=j;
        }
    }
    for(int i=0;i<sn;i++)rt[i]=i,pa[i][0]=i;
    for(int i=0;i<sn;i++)if(scc[i].size()>1)sdfs(i,i,i);
    for(int u=0;u<sn;u++)for(int i=1;i<22;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
}

int send_ball(int c, int s, ll t){
    int sid=sccid[calc(s,c)];
    if(t<1ll*lv[sid]){
        for(int i=21;i>=0;i--){
            if((1ll<<i)>t)continue;
            t-=1ll<<i;
            sid=pa[sid][i];
        }
        return scc[s][0]/(k+1);
    }
    t-=lv[sid];
    int sz=scc[rt[sid]].size();
    if(rt[sid]==sid)t+=spos[calc(s,c)];
    return scc[rt[sid]][(t+pos[sid])%sz]/(k+1);
}

