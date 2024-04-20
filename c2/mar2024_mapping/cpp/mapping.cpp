#include "mapping.h"
#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=1005;

int n,s;
vector<int> adj[N];
vector<pair<int,int>> ans;
int sz[N],par[N],pos[N];
int rt;
bool used[N];

bool ask(int x,int u,int v){
    bool res=send_signal(x,u,v);
    if(s!=-1)res^=abs(pos[u]-pos[v])==1;
    return res;
}

void link(int u,int v){
    ans.emplace_back(u,v);
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
}

int get_sz(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
    return sz[u];
}

tuple<int,int,int> find_edge(int u,int cnt,int p=0){
    tuple<int,int,int> res(p?-max(sz[u],cnt-sz[u]):-cnt-1,p,u);
    for(auto v:adj[u])if(v!=p&&!used[v]){
        res=max(res,find_edge(v,cnt,u));
    }
    return res;
}

void mergesort(vector<int> &a,int l,int r){
    if(l==r)return;
    int m=(l+r)/2;
    mergesort(a,l,m);
    mergesort(a,m+1,r);
    vector<int> b;
    for(int i=l,j=m+1;i<=m||j<=r;){
        if(j>r||(i<=m&&send_signal(rt,a[i],a[j]))){
            b.emplace_back(a[i++]);
        }else{
            b.emplace_back(a[j++]);
        }
    }
    for(auto x:b)a[l++]=x;
}

vector<pair<int,int>> mapping(int _n,int _s){
    n=_n,s=_s;
    rt=s==-1?1:s;
    vector<int> ord;
    for(int i=1;i<=n;i++)if(i!=rt)ord.emplace_back(i);
    shuffle(ord.begin(),ord.end(),rng);
    mergesort(ord,0,n-2);
    if(s!=-1){
        int pre=rt;
        for(int i=0;i<n-1;i++){
            if(!send_signal(pre,ord[i],pre)){
                int j=i+1;
                while(j<n-1&&send_signal(ord[j],ord[j-1],ord[j]))j++;
                reverse(ord.begin()+i,ord.begin()+j);
                i=j-1;
            }
            pre=ord[i];
        }
        pos[rt]=1;
        for(int i=0;i<n-1;i++)pos[ord[i]]=i+2;
    }
    for(auto x:ord){
        for(int i=1;i<=n;i++)used[i]=false;
        auto [_,v,u]=find_edge(rt,get_sz(rt));
        while(v){
            if(ask(x,v,u)){
                used[u]=true;
                u=v;
            }else{
                used[v]=true;
            }
            tie(_,v,u)=find_edge(u,get_sz(u));
        }
        link(u,x);
    }
    return ans;
}
