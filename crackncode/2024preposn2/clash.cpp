#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;

int n;
ll s[10],t[N];
ll dp[2][N];
vector<int> state;

int encode(int a,int b,int c,int d){
    return a<<9|b<<6|c<<3|d;
}

tuple<int,int,int,int> decode(int x){
    return {x>>9,x>>6&7,x>>3&7,x&7};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<8;i++)cin >> s[i];
    for(int i=1;i<=n;i++)cin >> t[i];
    for(int i=0;i<8;i++)for(int j=0;j<8;j++)if(j!=i)for(int k=0;k<8;k++)if(k!=i&&k!=j){
        for(int l=0;l<8;l++)if(l!=i&&l!=j&&l!=k)state.emplace_back(encode(i,j,k,l));
    }
    for(int i=1;i<=n;i++)for(auto mask:state){
        auto [a,b,c,d]=decode(mask);
        ll res=dp[i&1^1][mask];
        for(int j=0;j<8;j++)if(j!=a&&j!=b&&j!=c&&j!=d){
            ll &x=dp[i&1][encode(b,c,d,j)];
            x=max(x,res+abs(t[i]-s[j]));
        }
    }
    ll ans=0;
    for(auto i:state)ans=max(ans,dp[n&1][i]);
    cout << ans;
}