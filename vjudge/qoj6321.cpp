#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using tlll = tuple<ll,ll,ll>;

const ll mod=998244353;

int n;
vector<pair<ll,ll>> a[5];
vl f[5];
vector<tlll> vec;
ll ans;

void solve(int b,int c,int d,int e){
    for(auto [x,t]:a[0])ans=(ans+x*f[b][t]%mod*f[c][t]%mod*(n-f[d][t])%mod*(n-f[e][t])%mod)%mod;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<5;i++)f[i].resize(5*n);
    for(int i=0;i<5;i++)for(int j=0;j<n;j++){
        ll x;
        cin >> x;
        vec.emplace_back(x,i,j);
    }
    sort(vec.begin(),vec.end());
    for(int t=0;t<5*n;t++){
        auto [x,i,j]=vec[t];
        a[i].emplace_back(x,t);
        f[i][t]++;
    }
    for(int i=0;i<5;i++)for(int j=1;j<5*n;j++)f[i][j]+=f[i][j-1];
    for(int i=0;i<5;i++){
        swap(a[0],a[i]),swap(f[0],f[i]);
        solve(1,2,3,4);
        solve(1,3,2,4);
        solve(1,4,2,3);
        solve(2,3,1,4);
        solve(2,4,1,3);
        solve(3,4,1,2);
    }
    cout << ans;
}