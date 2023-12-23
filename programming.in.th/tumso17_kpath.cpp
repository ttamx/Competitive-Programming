#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;
const int inf=1e9;

int n,k;
vector<p2> adj[N];
int sz[N];
bool used[N];
int ans=inf;
vector<int> vec;

int dfssz(int u,int p=-1){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,int d,int p=-1){
    vec.emplace_back(d);
    if(d>k)return;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])dfs(v,d+w,u);
}

void decom(int u){
    u=centroid(u,dfssz(u));
    used[u]=true;
    set<int> s;
    s.emplace(0);
    for(auto [v,w]:adj[u])if(!used[v]){
        dfs(v,w);
        for(auto d:vec){
            auto it=s.lower_bound(k-d);
            if(it!=s.end())ans=min(ans,*it+d-k);
            if(it!=s.begin())ans=min(ans,k-*prev(it)-d);
        }
        for(auto d:vec)s.emplace(d);
        vec.clear();
    }
    for(auto [v,w]:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    decom(1);
    cout << ans;
}