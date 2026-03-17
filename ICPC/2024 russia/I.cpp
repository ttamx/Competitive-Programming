#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n+2;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int p=-1;
    for(int i=0;i<n;i++){
        if(adj[i].size()==4){
            p=i;
            break;
        }
    }
    assert(p!=-1);
    vector<bool> vis(n);
    int tail=0,body=1;
    for(auto u:adj[p]){
        if(vis[u])continue;
        int x=p;
        int cnt=1;
        while(adj[u].size()==2){
            vis[u]=true;
            swap(u,x);
            u^=adj[x][0]^adj[x][1];
            cnt++;
        }
        if(adj[u].size()==4){
            tail+=cnt;
        }else{
            body+=cnt;
        }
    }
    cout << n+3-body-tail << " " << body << " " << tail << "\n";
}