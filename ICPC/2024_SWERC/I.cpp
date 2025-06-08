#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<n;i++){
        int m;
        cin >> m;
        while(m--){
            int x;
            cin >> x;
            x--;
            adj[i].emplace_back(x);
            deg[x]++;
        }
    }
    vector<int> q;
    for(int i=0;i<n;i++)if(deg[i]==0)q.emplace_back(i);
    for(int i=0;i<q.size();i++){
        int u=q[i];
        for(auto v:adj[u]){
            if(--deg[v]==0){
                q.emplace_back(v);
            }
        }
    }
    if(q.size()==n){
        bool ok=true;
        for(int i=0;i+1<n;i++){
            int u=q[i],v=q[i+1];
            bool found=false;
            for(auto x:adj[u]){
                if(x==v){
                    found=true;
                    break;
                }
            }
            if(!found){
                ok=false;
                break;
            }
        }
        cout << ok << "\n";
    }else{
        cout << 0 << "\n";
    }
}