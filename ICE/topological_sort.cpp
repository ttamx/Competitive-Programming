#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m;
int deg_in[N];
vector<int> adj[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        deg_in[v]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++)if(deg_in[i]==0)q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout << u << ' ';
        for(auto v:adj[u]){
            deg_in[v]--;
            if(deg_in[v]==0)q.push(v);
        }
    }
}