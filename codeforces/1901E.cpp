#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf=1e18;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<int>> adj(n+2);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    ll ans=0;
    vector<ll> dp(n+2,-inf),dp1(n+2,-inf),dp2(n+2,-inf),dp3(n+2,-inf);
    function<void(int,int)> dfs=[&](int u,int p){
        vector<ll> vec;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            vec.emplace_back(dp[v]);
        }
        sort(vec.rbegin(),vec.rend());
        if(vec.size()>=2)dp2[u]=max(dp2[u],vec[0]+vec[1]);
        if(vec.size()>=3){
            ll sum=a[u];
            for(int i=0;i<vec.size();i++)if(i<3||vec[i]>0)sum+=vec[i];
            dp3[u]=max(dp3[u],sum);
        }
        if(!vec.empty())dp1[u]=max(dp1[u],vec[0]);
        dp[u]=max({a[u],dp1[u],dp2[u]+a[u],dp3[u]});
        ans=max({ans,a[u],dp1[u]+a[u],dp2[u],dp3[u]});
    };
    int rt=0;
    for(int i=1;i<=n;i++)if(adj[i].size()==1)rt=i;
    dfs(rt,0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}