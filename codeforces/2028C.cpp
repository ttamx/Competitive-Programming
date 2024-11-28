#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m,v;
    cin >> n >> m >> v;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> dpl(n),dpr(n);
    for(int t=0;t<2;t++){
        ll sum=0;
        for(int r=0,l=0;r<n;r++){
            sum+=a[r];
            while(sum-a[l]>=v){
                sum-=a[l];
                l++;
            }
            if(sum>=v){
                dpl[r]=(l==0?0:dpl[l-1])+1;
            }
        }
        reverse(a.begin(),a.end());
        swap(dpl,dpr);
    }
    reverse(dpr.begin(),dpr.end());
    if(dpl.back()<m){
        cout << -1 << "\n";
        return;
    }
    ll ans=0;
    for(int i=1;i<n;i++){
        a[i]+=a[i-1];
    }
    for(int l=0,r=0;r<n;r++){
        int cur=(r+1<n?dpr[r+1]:0);
        while(cur+(l>0?dpl[l-1]:0)<m){
            l++;
        }
        ans=max(ans,a[r]-(l>0?a[l-1]:0LL));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}