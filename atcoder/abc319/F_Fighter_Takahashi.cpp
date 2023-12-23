#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=505;
const int inf=1e9;

int n;
int p[N],t[N],s[N],g[N],pa[N];
int pos[N];
vector<int> adj[N];
vector<int> med;
set<p2> st[12];

void dfs(int u){
    for(auto v:adj[u]){
        if(t[u]==2)pa[v]=pos[u];
        else pa[v]=pa[u];
        dfs(v);
    }
}

void construct(int id){
    auto upd=[&](int l,int r){
        auto it=st[id].lower_bound(make_pair(l+1,0));
        if(it!=st[id].begin()&&(--it)->second>=l){
            l=it->first;
            r=min(r+it->second,inf);
            st[id].erase(it);
        }else{
            r=min(r+l,inf);
        }
        st[id].emplace(l,r);
    };
    priority_queue<p2,vector<p2>,greater<p2>> pq;
    pq.emplace(0,med[id]);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>0)upd(d,g[u]);
        for(auto v:adj[u]){
            if(t[v]==2)continue;
            pq.emplace(s[v],v);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    med.emplace_back(1);
    for(int i=2;i<=n;i++){
        cin >> p[i] >> t[i] >> s[i] >> g[i];
        adj[p[i]].emplace_back(i);
        if(t[i]==2){
            pos[i]=med.size();
            med.emplace_back(i);
        }
    }
    dfs(1);
    for(int i=0;i<med.size();i++)construct(i);
    
}