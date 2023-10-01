#include<bits/stdc++.h>

using namespace std;

const int N=5005;

int n;
vector<int> adj[N];
int ans[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        queue<tuple<int,int,int>> q;
        q.emplace(0,i,0);
        int sum=0;
        for(int j=1;j<=n;j++){
            auto [d,u,p]=q.front();
            q.pop();
            sum+=d;
            ans[j]=max(ans[j],(n-1)*j-2*sum);
            for(auto v:adj[u])if(v!=p)q.emplace(d+1,v,u);
        }
    }
    for(int i=0;i<=n;i++)cout << ans[i] << " \n"[i==n];
}