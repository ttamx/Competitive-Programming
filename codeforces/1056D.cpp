#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
vector<int> adj[N];
int a[N],c[N];
int ans[N];

void dfs(int u){
    for(auto v:adj[u]){
        dfs(v);
        a[u]+=a[v];
    }
    a[u]=max(a[u],1);
    c[a[u]]++;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        for(int j=0;j<c[i];j++){
            cout << i << " ";
        }
    }
    cout << "\n";
}