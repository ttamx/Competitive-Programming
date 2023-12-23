#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;
const ll inf=1e18;

int n,k;
vector<pair<int,int>> adj[N];
pair<ll,int> dp[N][2];

pair<ll,int> operator+(pair<ll,int> l,pair<ll,int> r){
    return pair<ll,int>(l.first+r.first,l.second+r.second);
}

pair<ll,int> operator-(pair<ll,int> l,pair<ll,int> r){
    return pair<ll,int>(l.first-r.first,l.second-r.second);
}

void dfs(ll lambda,int u=1,int p=-1){
    dp[u][0]=dp[u][1]=pair<ll,int>(0ll,0);
    for(auto x:adj[u]){
        int v,w;
        tie(v,w)=x;
        if(v==p)continue;
        dfs(lambda,v,u);
        dp[u][0]=dp[u][0]+dp[v][1];
        auto res=dp[v][0]-dp[v][1];
        res.first+=w-lambda;
        res.second++;
        dp[u][1]=max(dp[u][1],res);
    }
    dp[u][1]=dp[u][0]+dp[u][1];
}

ll cdiv(ll a,ll b){
    return a/b+((a^b)>0&&a%b);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    ll l=-inf,r=inf;
    while(l<r){
        ll m=cdiv(l+r,2);
        dfs(m);
        if(dp[1][1].second>=k)l=m;
        else r=m-1;
    }
    dfs(l);
    cout << (l==-inf?-1:dp[1][1].first+l*k) << "\n";
}