#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll sum=0;
    vl a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
        sum+=a[i];
    }
    int m=n/2;
    map<ll,ll> mp;
    for(int mask=0;mask<1<<m;mask++){
        ll res=0,res2=0;
        for(int i=0;i<m;i++)if(mask>>i&1){
            res+=a[i]+b[i];
            res2+=b[i];
        }
        auto it=mp.find(res);
        if(it==mp.end()){
            mp[res]=res2;
        }else if(res2<it->second){
            it->second=res2;
        }
    }
    ll ans=LINF;
    for(int mask=0;mask<1<<(n-m);mask++){
        ll res=0,res2=0;
        for(int i=0;i<n-m;i++)if(mask>>i&1){
            res+=a[m+i]+b[m+i];
            res2+=b[m+i];
        }
        auto it=mp.find(sum-res);
        if(it!=mp.end()){
            ans=min(ans,it->second+res2);
        }
    }
    cout << (ans==LINF?-1:ans);
}