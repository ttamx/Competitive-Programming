#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1e4+5;

int n,k,t,ans=-1;
int lv[N],mn[N],deg[N],cnt[N];
bool vis[N];
vector<int> adj[N];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

void dfs(int u){
    if(vis[u])return;
    vis[u]=true;
    for(auto v:adj[u]){
        dfs(v);
        mn[u]=min(mn[u],mn[v]);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> t;
    for(int i=1;i<=n;i++){
        int p;
        cin >> lv[i] >> p;
        mn[i]=lv[i];
        cnt[lv[i]]++;
        for(int j=0;j<p;j++){
            int v;
            cin >> v;
            adj[v].push_back(i);
            deg[i]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(deg[i]==0){
            dfs(i);
            pq.emplace(mn[i],i);
        }
    }
    while(!pq.empty()&&t--){
        auto [l,u]=pq.top();
        pq.pop();
        cnt[lv[u]]--;
        for(auto v:adj[u])if(--deg[v]==0)pq.emplace(mn[v],v);
    }
    for(int i=1;i<=k;i++){
        if(cnt[i]==0)ans=i;
        else break;
    }
    cout << ans;
}