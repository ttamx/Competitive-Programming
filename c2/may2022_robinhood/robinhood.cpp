#include "robinhood.h"
#include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

struct node{
    int val,l,r,p;
}t[N];

int n;
int dp[N][20];
int sz[N],cp[N],lv[N];
int a[N];
bool used[N];
vector<pair<int,int>> adj[N];

int dfs(int u,int p=0){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
    return u;
}

void getdis(int u,int p,int l){
    for(auto [v,w]:adj[u]){
        if(used[v]||v==p)continue;
        dp[v][l]=dp[u][l]+w;
        getdis(v,u,l);
    }
}

void decom(int u,int p=0,int l=0){
    u=centroid(u,dfs(u));
    used[u]=true;
    cp[u]=p;
    lv[u]=l;
    for(auto [v,w]:adj[u]){
        if(used[v])continue;
        dp[v][l]=w;
        getdis(v,u,l);
    }
    for(auto [v,w]:adj[u])if(!used[v])decom(v,u,l+1);
}

pair<pair<int,int>,pair<int,int>> mn[N];

void update(int st){
    for(int u=st,ch=0;u!=0;u=cp[u],ch=st){
        pair<int,int> tmp(dp[st][lv[u]],ch);
        if(mn[u].first.second==ch)mn[u].first=min(mn[u].first,tmp);
        else mn[u].second=min(mn[u].second,tmp);
        if(mn[u].first>mn[u].second)swap(mn[u].first,mn[u].second);
    }
}

int query(int st){
    int res=1e9;
    for(int u=st,ch=0;u!=0;u=cp[u],ch=st)res=min(res,dp[st][lv[u]]+(ch==0||ch!=mn[u].first.second?mn[u].first.first:mn[u].second.first));
    return res;
}

void initialize(vector<int> A, int M){
    n=A.size();
    for(int i=1;i<=n;i++){
        a[i]=A[i-1];
        mn[i]={{1e9,0},{1e9,0}};
    }
    int rt=1,lf=1;
    t[0].val=1e9;
    t[1].val=a[1];
    for(int i=2;i<=n;i++){
        while(a[i]>=t[lf].val)lf=t[lf].p;
        if(lf==0){
            t[rt].p=i;
            t[i].l=rt;
            rt=lf=i;
        }else{
            t[i].l=t[lf].r;
            t[t[lf].r].p=i;
            t[lf].r=i;
            t[i].p=lf;
            lf=i;
        }
        t[i].val=a[i];
    }
    for(int i=1;i<=n;i++){
        if(t[i].p){
            adj[i].emplace_back(t[i].p,t[t[i].p].val-t[i].val);
            adj[t[i].p].emplace_back(i,t[t[i].p].val-t[i].val);
        }
    }
    decom(rt);
    update(1);
}

int ask(int v){
    v++;
    return (query(v)+a[v])/2;
}

void add(int v){
    v++;
    update(v);
}