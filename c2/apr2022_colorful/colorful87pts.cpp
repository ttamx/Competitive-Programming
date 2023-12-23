#include "colorful.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> p2;

const int N=5e4+5;
const int K=405;
const int NK=N*K;

int n,m,k,cnt;
int prime[K];
bool notprime[3000];
vector<int> xy[N];
int nxt[NK],cyc[NK],sz[NK];
vector<int> com[NK];
bool vis[NK];
int pos[NK];

int calc(int x,int y){
    return x*k+y;
}

string print(int x){
    return "("+to_string(x/k)+","+to_string(x%k)+")";
}

int dfs(int u){
    if(vis[u])return cyc[u];
    vis[u]=true;
    cyc[u]=dfs(nxt[u]);
    cnt++;
    if(sz[cyc[u]]==0)com[cyc[u]].push_back(u);
    if(u==cyc[u])sz[cyc[u]]=cnt;
    return cyc[u];
}

void init_machine(int N, int M, int K, int Q, vector<int> x, vector<int> y){
    n=N,m=M,k=K;
    for(int cnt=0,i=2;cnt<k;i++){
        if(notprime[i])continue;
        prime[cnt++]=i;
        for(int j=i;j<3000;j+=i)notprime[j]=true;
    }
    for(int i=0;i<m;i++){
        int u=x[i],v=y[i];
        xy[u].push_back(v);
        xy[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            int mn=2e9,nv=i;
            for(auto v:xy[i]){
                if(v%prime[j]<mn){
                    mn=v%prime[j];
                    nv=v;
                }else if(mn==v%prime[j]){
                    nv=min(nv,v);
                }
            }
            int u=calc(i,j);
            int v=calc(nv,(j+1)%k);
            nxt[u]=v;
            cyc[u]=u;
            pos[u]=-1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            cnt=0;
            dfs(calc(i,j));
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            int u=calc(i,j);
            if(u!=cyc[u])continue;
            sz[cyc[u]]=com[cyc[u]].size();
            reverse(com[u].begin(),com[u].end());
            for(int l=0;l<sz[cyc[u]];l++)pos[com[u][l]]=l;
        }
    }
}

int send_ball(int c, int s, ll t){
    int cur=calc(s,c);
    while(t&&pos[cur]==-1){
        cur=nxt[cur];
        t--;
    }
    if(pos[cur]==-1)return cur/k;
    t+=pos[cur];
    t%=sz[cyc[cur]];
    return com[cyc[cur]][t]/k;
}

