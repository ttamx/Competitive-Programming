#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

struct Z{
    ll x;
    Z():x(0){}
    Z(ll x):x(x%mod){}
    Z& operator+=(Z o){x=(x+o.x)%mod;return *this;}
    Z& operator-=(Z o){x=(x+mod-o.x)%mod;return *this;}
    Z& operator*=(Z o){x=(x*o.x)%mod;return *this;}
    friend Z operator+(Z a,Z b){return a+=b;}
    friend Z operator-(Z a,Z b){return a-=b;}
    friend Z operator*(Z a,Z b){return a*=b;}
};

int n;
vector<int> adj[N];
Z dp[N][2];

void dfs(int u,int p){
    dp[u][0]=dp[u][1]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[u][0]*=(dp[v][0]+dp[v][1]);
        dp[u][1]*=dp[v][0];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    cout << (dp[1][0]+dp[1][1]).x;
}