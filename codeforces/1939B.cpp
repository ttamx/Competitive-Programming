#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=4e5+5;

int n,g;
int w[N],deg[N],sz[N],deg2[N];
multiset<pair<int,int>> s[N];
vector<pair<int,int>> adj[N];
vector<int> adj2[M],adj3[N];
queue<int> q;
pair<int,int> edge[N];
int cnt=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> g;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v >> w[i];
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
        deg[u]++,deg[v]++;
    }
    for(int i=1,id=0;i<=n;i++)for(int j=0;j<deg[i];j++){
        int x;
        cin >> x;
        s[i].emplace(x,++id);
    }
    for(int i=1;i<=n;i++)sz[i]=sz[i-1]+deg[i];
    for(int i=1;i<=n;i++)if(deg[i]==1)q.emplace(i);
    while(!q.empty()&&cnt<n-1){
        int u=q.front();
        q.pop();
        auto [val,x]=*s[u].begin();
        s[u].clear();
        for(auto [v,i]:adj[u])if(!s[v].empty()){
            auto it=s[v].lower_bound({w[i]-val,0});
            if(it==s[v].end())cout << "No",exit(0);
            int y=it->second;
            s[v].erase(it);
            cnt++;
            if(x<sz[u])adj2[x+1].emplace_back(i);
            if(y<sz[v])adj2[y+1].emplace_back(i);
            edge[i]={x,y};
            if(s[v].size()==1)q.emplace(v);
        }
    }
    if(cnt<n-1)cout << "No",exit(0);
    for(int i=1;i<n;i++){
        auto [u,v]=edge[i];
        for(auto j:adj2[u]){
            adj3[i].emplace_back(j);
            deg2[j]++;
        }
        for(auto j:adj2[v]){
            adj3[i].emplace_back(j);
            deg2[j]++;
        }
    }
    cout << "Yes\n";
    while(!q.empty())q.pop();
    for(int i=1;i<n;i++)if(deg2[i]==0)q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout << u << " ";
        for(auto v:adj3[u])if(--deg2[v]==0)q.emplace(v);
    }
}