#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int M=5e5+5;

int n,m;
vector<pair<int,int>> adj[N];
bool used[M];
vector<pair<int,int>> ans;

void dfs(int u){
    while(!adj[u].empty()){
        auto [v,i]=adj[u].back();
        adj[u].pop_back();
        if(used[i])continue;
        used[i]=true;
        dfs(v);
        ans.emplace_back(u,v);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    int idx=0;
    for(int i=1;i<=n;i++){
        if(adj[i].size()%2==1){
            if(idx){
                m++;
                adj[idx].emplace_back(i,m);
                adj[i].emplace_back(idx,m);
                idx=0;
            }else{
                idx=i;
            }
        }
    }
    assert(idx==0);
    dfs(1);
    if(ans.size()%2==1)ans.emplace_back(1,1);
    for(int i=0;i<ans.size();i+=2){
        swap(ans[i].first,ans[i].second);
    }
    cout << ans.size() << "\n";
    for(auto [u,v]:ans){
        cout << u << " " << v << "\n";
    }
}