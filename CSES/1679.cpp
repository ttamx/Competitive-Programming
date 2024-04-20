#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
vector<int> adj[N];
queue<int> q;
vector<int> ans;
int deg[N]; //in-degree

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        deg[v]++;
    }
    for(int i=1;i<=n;i++){
        if(deg[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ans.push_back(u);
        for(auto v:adj[u]){
            deg[v]--;
            if(deg[v]==0){
                q.push(v);
            }
        }
    }
    if(ans.size()<n){
        cout << "IMPOSSIBLE";
    }else{
        for(auto x:ans)cout << x << " ";
    }
}