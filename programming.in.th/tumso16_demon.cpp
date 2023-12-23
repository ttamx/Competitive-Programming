#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m;
int a[N];
long long dp[N];
vector<int> adj[N];
vector<int> q;
set<int> s[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    for(int i=1;i<=n;i++)cin >> a[i];
    q.emplace_back(1);
    for(int i=0;i<n;i++)for(auto v:adj[q[i]])q.emplace_back(v);
    for(int i=n-1;i>=0;i--){
        int u=q[i];
        int mx=0;
        for(auto v:adj[u])if(s[v].size()>s[mx].size())mx=v;
        swap(s[u],s[mx]);
        dp[u]=dp[mx];
        if(s[u].emplace(a[u]).second)dp[u]+=a[u];
        for(auto v:adj[u]){
            if(v==mx)continue;
            for(auto x:s[v])if(s[u].emplace(x).second)dp[u]+=x;
            s[v].clear();
        }
    }
    while(m--){
        int u;
        cin >> u;
        cout << dp[u] << '\n';
    }
}