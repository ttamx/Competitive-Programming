#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

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

const int X=2e6;

void runcase(){
    int n;
    ll d;
    cin >> n >> d;
    vector<ll> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    auto sa=a;
    auto sb=b;
    for(int i=1;i<n;i++){
        sa[i]+=sa[i-1];
        sb[i]+=sb[i-1];
    }
    auto calcx=[&](ll x){
        int i=lower_bound(a.begin(),a.end(),x)-a.begin();
        ll res=0;
        if(i>0){
            res+=x*i-sa[i-1];
        }
        if(i<n){
            res+=sa[n-1]-(i?sa[i-1]:0LL)-(n-i)*x;
        }
        return res;
    };
    auto calcy=[&](ll x){
        int i=lower_bound(b.begin(),b.end(),x)-b.begin();
        ll res=0;
        if(i>0){
            res+=x*i-sb[i-1];
        }
        if(i<n){
            res+=sb[n-1]-(i?sb[i-1]:0LL)-(n-i)*x;
        }
        return res;
    };
    vector<int> cnt(d+1);
    for(int i=-X;i<=X;i++){
        ll res=calcx(i);
        if(res<=d){
            cnt[res]++;
        }
    }
    for(int i=1;i<=d;i++){
        cnt[i]+=cnt[i-1];
    }
    ll ans=0;
    for(int i=-X;i<=X;i++){
        ll res=d-calcy(i);
        if(res>=0){
            ans+=cnt[res];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}