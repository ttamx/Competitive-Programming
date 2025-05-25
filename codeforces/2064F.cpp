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
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<pair<int,int>> sl,sr;
    vector<vector<pair<int,int>>> add(n),del(n);
    for(int i=n-1;i>=0;i--){
        int sz=1;
        while(!sr.empty()&&sr.back().first<a[i]){
            add[i].emplace_back(sr.back());
            sz+=sr.back().second;
            sr.pop_back();
        }
        sr.emplace_back(a[i],sz);
        del[i].emplace_back(sr.back());
    }
    vector<ll> fl(2*n+1),fr(2*n+1);
    for(auto [val,cnt]:sr){
        fr[val]+=cnt;
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        vector<pair<int,int>> lc,rc;
        int sz=1;
        while(!sl.empty()&&sl.back().first>a[i]){
            auto [val,cnt]=sl.back();
            sl.pop_back();
            fl[val]-=cnt;
            sz+=cnt;
        }
        sl.emplace_back(a[i],sz);
        fl[a[i]]+=sz;
        lc.emplace_back(a[i],sz);
        for(auto [val,cnt]:add[i]){
            fr[val]+=cnt;
            rc.emplace_back(val,cnt);
        }
        for(auto [val,cnt]:del[i]){
            fr[val]-=cnt;
        }
        for(auto [val,cnt]:lc){
            if(val<=k){
                ans+=fr[k-val]*cnt;
            }
        }
        for(auto [val,cnt]:rc){
            if(val<=k){
                ans+=fl[k-val]*cnt;
            }
        }
        for(auto [val1,cnt1]:lc){
            for(auto [val2,cnt2]:rc){
                if(val1+val2==k){
                    ans-=1LL*cnt1*cnt2;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}