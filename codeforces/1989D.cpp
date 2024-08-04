#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n),c(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(auto &x:c)cin >> x;
    int mx=*max_element(a.begin(),a.end());
    vector<int> pre(mx+1,INF),dp(mx+1);
    for(int i=0;i<n;i++)pre[a[i]]=min(pre[a[i]],a[i]-b[i]);
    for(int i=1;i<=mx;i++)pre[i]=min(pre[i],pre[i-1]);
    for(int i=1;i<=mx;i++)if(pre[i]<INF)dp[i]=dp[i-pre[i]]+1;
    ll ans=0;
    for(auto x:c){
        if(x>mx){
            int t=(x-mx)/pre[mx]+1;
            ans+=2*t;
            x-=pre[mx]*t;
        }
        ans+=2*dp[x];
    }
    cout << ans;
}