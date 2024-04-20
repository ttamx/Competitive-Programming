#include "mapping.h"
#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=1005;

int n,s;
vector<int> adj[N];
vector<pair<int,int>> cen[N];
vector<pair<int,int>> ans;
int sz[N],par[N],sz2[N],pos[N];
int rt;
bool used[N],vis[N];

bool ask(int x,int u,int v){
    bool res=send_signal(x,u,v);
    if(s!=-1)res^=abs(pos[u]-pos[v])==1;
    return res;
}

int get_sz(int u,int p=0){
    sz[u]=adj[u].size()<3;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

int decom(int u){
    u=centroid(u,get_sz(u));
    used[u]=true;
    for(auto v:adj[u])if(!used[v]){
        int c=decom(v);
        par[c]=u;
        cen[u].emplace_back(v,c);
    }
    return u;
}

void dfs(int u){
    sz2[u]=adj[u].size()<3;
    for(auto [_,v]:cen[u]){
        dfs(v);
        sz2[u]+=sz2[v];
    }
}

int build(){
    for(int i=1;i<=n;i++){
        par[i]=0;
        used[i]=false;
        vis[i]=false;
        cen[i].clear();
        sz2[i]=0;
    }
    int u=decom(rt);
    dfs(u);
    return u;
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
        int u=build();
        while(true){
            vis[u]=true;
            bool found=false;
            int cnt=0;
            shuffle(cen[u].begin(),cen[u].end(),rng);
            for(auto [v,c]:cen[u])if(vis[v]||!sz2[c])cnt++;
            for(auto [v,c]:cen[u])if(!vis[v]&&sz2[c]){
                cnt++;
                if(cnt>2||ask(x,v,u)){
                    u=c;
                    found=true;
                    break;
                }
            }
            if(!found)break;
        }
        ans.emplace_back(u,x);
        adj[u].emplace_back(x);
        adj[x].emplace_back(u);
    }
    return ans;
}
