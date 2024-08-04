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

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    ll ans=0;
    auto calc=[&](int x){
        ll cnt=0;
        ans=0;
        for(int i=0;i<n;i++){
            if(a[i]<x)continue;
            int d=a[i]-x;
            int t=d/b[i]+1;
            ll res=1LL*(2*a[i]-(t-1)*b[i])*t/2;
            ans+=res;
            cnt+=t;
        }
        return cnt;
    };
    int l=0,r=1e9+1;
    while(l<r){
        int m=(l+r)/2;
        if(calc(m)<=k)r=m;
        else l=m+1;
    }
    k-=calc(l);
    for(int i=0;i<n;i++){
        if(a[i]<l)continue;
        int d=a[i]-l;
        int t=d/b[i]+1;
        a[i]-=t*b[i];
    }
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<n;i++)if(a[i]>0)pq.emplace(a[i],i);
    while(!pq.empty()&&k>0){
        auto [v,i]=pq.top();
        pq.pop();
        ans+=v;
        a[i]-=b[i];
        if(a[i]>0)pq.emplace(a[i],i);
        k--;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}