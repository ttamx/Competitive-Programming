#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        deg[v]++;
    }
    queue<int> q;
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            q.emplace(i);
        }
    }
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cnt++;
        for(auto v:adj[u]){
            if(--deg[v]==0){
                q.emplace(v);
            }
        }
    }
    if(cnt==n){
        cout << "YES\n";
        exit(0);
    }
    for(int i=0;i<n;i++){
        if(deg[i]==1){
            int cnt2=cnt;
            auto deg2=deg;
            q.emplace(i);
            while(!q.empty()){
                int u=q.front();
                q.pop();
                cnt2++;
                for(auto v:adj[u]){
                    if(v!=i&&--deg2[v]==0){
                        q.emplace(v);
                    }
                }
            }
            if(cnt2==n){
                cout << "YES\n";
                exit(0);
            }
        }
    }
    cout << "NO\n";
}