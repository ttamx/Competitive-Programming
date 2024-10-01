#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,a,b;
    cin >> n >> m >> a >> b;
    if(a>b)swap(a,b);
    vector<vector<int>> adj(n);
    vector<int> id;
    int c=0;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        if(w<=a){
            cout << -1;
            exit(0);
        }
        if(w<=b){
            c++;
        }
        u--,v--;
        if(u>v)swap(u,v);
        id.emplace_back(u);
        id.emplace_back(v);
        adj[u].emplace_back(v);
    }
    id.emplace_back(0);
    id.emplace_back(n-1);
    sort(id.begin(),id.end());
    id.erase(unique(id.begin(),id.end()),id.end());
    int s=id.size();
    for(auto &v:adj){
        sort(v.begin(),v.end());
    }
    vector<vector<int>> dp(s,vector<int>(s));
    for(int r=0;r<s;r++){
        int cur=0;
        for(int l=r;l>=0;l--){
            cur+=upper_bound(adj[id[l]].begin(),adj[id[l]].end(),id[r])-adj[id[l]].begin();
            dp[l][r]=cur;
        }
    }
    vector<vector<int>> dp2(s+1,vector<int>(c+1,n-1));
    dp2[0][0]=0;
    for(int i=0;i<s;i++){
        for(int j=0;j<=c;j++){
            dp2[i+1][j]=min(dp2[i+1][j],dp2[i][j]);
            for(int k=i+1;k<=s;k++){
                int x=min(j+dp[i][k-1],c);
                dp2[k][x]=min(dp2[k][x],dp2[i][j]+id[k-1]-id[i]);
            }
        }
    }
    int v=dp2[s][c];
    cout << 1LL*a*v+1LL*(n-1-v)*b;
}