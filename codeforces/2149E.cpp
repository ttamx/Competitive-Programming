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
    int n,k,l,r;
    cin >> n >> k >> l >> r;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(auto &x:a){
        x=lower_bound(b.begin(),b.end(),x)-b.begin();
    }
    multiset<int,greater<int>> msl,msr;
    auto insert=[&](int x){
        msl.emplace(x);
        if(msl.size()>k){
            auto it=prev(msl.end());
            msr.emplace(*it);
            msl.erase(it);
        }
    };
    auto erase=[&](int x){
        auto it=msl.find(x);
        if(it!=msl.end()){
            msl.erase(it);
            if(!msr.empty()){
                msl.emplace(*msr.begin());
                msr.erase(msr.begin());
            }
        }else{
            msr.erase(msr.find(x));
        }
    };
    ll ans=0;
    vector<int> pre(n,-1);
    for(int i=0;i<n;i++){
        if(pre[a[i]]!=-1){
            erase(pre[a[i]]);
        }
        insert(pre[a[i]]=i);
        if(msl.size()==k){
            int lo=i-*msl.rbegin()+1;
            int hi=i+1;
            if(!msr.empty()){
                hi=i-*msr.begin();
            }
            ans+=max(min(hi,r)-max(lo,l)+1,0);
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