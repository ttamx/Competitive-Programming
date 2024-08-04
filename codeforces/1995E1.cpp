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
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(2*n);
    for(auto &x:a)cin >> x;
    if(n%2==0){
        for(int i=0;i<n;i+=2){
            ll d1=abs(a[i]+a[i+1]-a[i+n]-a[i+n+1]);
            ll d2=abs(a[i+n]+a[i+1]-a[i]-a[i+n+1]);
            if(d2<d1){
                swap(a[i],a[i+n]);
            }
        }
        ll mn=LINF,mx=-LINF;
        for(int i=0;i<2*n;i+=2){
            ll val=a[i]+a[i+1];
            mn=min(mn,val);
            mx=max(mx,val);
        }
        cout << mx-mn << "\n";
        return;
    }
    auto get=[&](int i,int s){
        if(s==0)return a[i];
        if(i<n)return a[i+n];
        else return a[i-n];
    };
    auto check=[&](ll l,ll r){
        auto valid=[&](ll x){
            return l<=x&&x<=r;
        };
        for(int t=0;t<2;t++){
            vector dp(n+1,array<bool,2>{false,false});
            dp[0][t]=true;
            int u=0,v=1;
            for(int i=1;i<=n;i++){
                for(int j=0;j<2;j++){
                    if(!dp[i-1][j])continue;
                    int val=get(u,j);
                    for(int k=0;k<2;k++){
                        if(valid(val+get(v,k))){
                            dp[i][k]=true;
                        }
                    }
                }
                u=v<n?v+n:v-n;
                v=u+1;
            }
            if(dp[n][t])return true;
        }
        return false;
    };
    vector<ll> vals;
    for(int i=0;i<2*n;i+=2){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                vals.emplace_back(get(i,j)+get(i+1,k));
            }
        }
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int m=vals.size();
    ll ans=LINF;
    for(int l=0,r=0;l<m;l++){
        while(r<m&&!check(vals[l],vals[r]))r++;
        if(r>=m)break;
        ans=min(ans,vals[r]-vals[l]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}