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
    int n,h;
    cin >> n >> h;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<ll> pre(n),suf(n);;
    for(int i=0;i<n;i++){
        ll mx=a[i];
        for(int j=i-1;j>=0;j--){
            mx=max(mx,a[j]);
            pre[i]+=h-mx;
        }
    }
    for(int i=n-1;i>=0;i--){
        ll mx=a[i];
        for(int j=i+1;j<n;j++){
            mx=max(mx,a[j]);
            suf[i]+=h-mx;
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        ll l=pre[i],r=suf[i];
        {
            ll cur=0;
            vector<pair<ll,ll>> st;
            for(int j=i+1;j<n;j++){
                if(a[j]>a[i])break;
                ll cc=1;
                while(!st.empty()&&st.back().first<a[j]){
                    auto [v,c]=st.back();
                    st.pop_back();
                    cur-=(h-v)*c;
                    cc+=c;
                }
                cur+=(h-a[j])*cc;
                st.emplace_back(a[j],cc);
                r=max(r,cur+suf[j]);
            }
        }
        {
            ll cur=0;
            vector<pair<ll,ll>> st;
            for(int j=i-1;j>=0;j--){
                if(a[j]>a[i])break;
                ll cc=1;
                while(!st.empty()&&st.back().first<a[j]){
                    auto [v,c]=st.back();
                    st.pop_back();
                    cur-=(h-v)*c;
                    cc+=c;
                }
                cur+=(h-a[j])*cc;
                st.emplace_back(a[j],cc);
                l=max(l,cur+pre[j]);
            }
        }
        ans=max(ans,l+r+h-a[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}