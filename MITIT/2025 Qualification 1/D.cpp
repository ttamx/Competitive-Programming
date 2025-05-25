#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> ans;
    int last=0;
    vector<int> a(k);
    for(auto &x:a){
        cin >> x;
        x--;
        if(x!=last){
            adj[last].emplace_back(x);
            adj[x].emplace_back(last);
            ans.emplace_back(last,x);
        }
        last=x;
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> d(n,n+1);
    queue<int> q;
    q.emplace(0);
    d[0]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(d[u]+1<d[v]){
                d[v]=d[u]+1;
                q.emplace(v);
            }
        }
    }
    for(int i=1;i<k;i++){
        if(d[a[i]]<=d[a[i-1]]){
            cout << -1 << "\n";
            return;
        }
    }
    cout << ans.size() << "\n";
    for(auto [u,v]:ans){
        cout << u+1 << " " << v+1 << "\n";
    } 
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}