#include<bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using pii = pair<int,int>;

const int N=2e5+5;

int n,m,k;
vector<pii> adj[N];
int degin[N],degout[N];
bool vis[N];
vi ans;

void dfs(int u,int e=0){
    if(vis[e])return;
    vis[e]=true;
    while(!adj[u].empty()){
        auto [v,ei]=adj[u].back();
        adj[u].pop_back();
        dfs(v,ei);
    }
    if(e)ans.emplace_back(e);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    k--;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        int u=0,l=s.size();
        while(u<l&&s[u]=='0')u++;
        if(u>=m)cout << -1,exit(0);
        for(int j=u;j<l;j++)if((s[j]=='1')^(j%m==u))cout << -1,exit(0);
        int v=(m+u-l%m)%m;
        adj[u].emplace_back(v,i);
        degin[v]++,degout[u]++;
    }
    int c=0;
    for(int i=0;i<m;i++){
        if(degout[i]-degin[i]==1){
            if(i!=k)cout << -1,exit(0);
        }else if(degin[i]-degout[i]==1){
            if(c++==1)cout << -1,exit(0);
        }else if(degin[i]!=degout[i]){
            cout << -1,exit(0);
        }
    }
    for(int i=0;i<m;i++)reverse(adj[i].begin(),adj[i].end());
    dfs(k);
    if(ans.size()!=n)cout << -1,exit(0);
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << " ";
}