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
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    vector<ll> pre(n+1),suf(n+1);
    suf[n]=LINF;
    for(int i=n-1;i>=0;i--){
        suf[i]=min(suf[i+1],a[i]);
    }
    pre[0]=LINF;
    for(int i=0;i<n;i++){
        pre[i+1]=min(pre[i],a[i]-i);
    }
    ll sum=accumulate(a.begin(),a.end(),0LL);
    while(q--){
        ll k;
        cin >> k;
        ll op=k<=n?k:((k-n)%2==1?n-1:n);
        ll neg=(k-op)/2;
        ll mn=min(pre[op]+k,suf[op]);
        cout << min((sum+((k+k-op+1)*op/2)-neg)/n,mn) << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}