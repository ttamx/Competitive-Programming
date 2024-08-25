#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Info{
    ll mx,mx2,ans;
    Info():mx(0),mx2(0),ans(0){}
    void upd(ll x){
        mx2=max(mx2,x);
        if(mx<mx2)swap(mx,mx2);
    }
};

void runcase(int n){
    vector<vector<pair<int,int>>> adj(n);
    for(int i=1;i<n;i++){
        int p,w;
        cin >> p >> w;
        p--;
        adj[p].emplace_back(i,w);
    }
    vector<Info> dp(n),up(n);
    ll ans=1e18;
    function<void(int)> dfs=[&](int u){
        for(auto [v,w]:adj[u]){
            dfs(v);
            dp[u].ans=max(dp[u].ans,dp[v].ans);
            dp[u].upd(dp[v].mx+w);
        }
        dp[u].ans=max(dp[u].ans,dp[u].mx+dp[u].mx2);
    };
    function<void(int)> dfs2=[&](int u){
        for(auto [v,w]:adj[u]){
            up[v].ans=up[u].ans;
            up[v].mx=up[u].mx;
        }
        for(int t=0;t<2;t++){
            Info sum;
            for(auto [v,w]:adj[u]){
                up[v].ans=max(up[v].ans,sum.ans);
                up[v].upd(sum.mx);
                up[v].upd(sum.mx2);
                sum.ans=max(sum.ans,dp[v].ans);
                sum.upd(dp[v].mx+w);
            }
            reverse(adj[u].begin(),adj[u].end());
        }
        for(auto [v,w]:adj[u]){
            up[v].ans=max(up[v].ans,up[v].mx+up[v].mx2);
            ans=min(ans,abs(dp[v].ans-up[v].ans));
            up[v].mx+=w;
            dfs2(v);
        }
    };
    dfs(0);
    dfs2(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        int n;
        cin >> n;
        if(n==0)break;
        runcase(n);
    }
}