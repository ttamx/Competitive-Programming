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
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n),d(n);
    for(auto &x:a)cin >> x;
    for(auto &x:d)cin >> x;
    vector<int> nxt(2*n,-1);
    {
        map<ll,int> mp;
        for(int i=0;i<n;i++){
            ll v=(a[i]+d[i])%k;
            if(mp.count(v)){
                nxt[i*2]=mp[v]*2+1;
            }
            mp[v]=i;
        }
    }
    {
        map<ll,int> mp;
        for(int i=n-1;i>=0;i--){
            ll v=(a[i]-d[i]+k)%k;
            if(mp.count(v)){
                nxt[i*2+1]=mp[v]*2;
            }
            mp[v]=i;
        }
    }
    vector<bool> dp(2*n),vis(2*n);
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        if(nxt[u]==-1){
            dp[u]=true;
        }else{
            dfs(nxt[u]);
            dp[u]=dp[nxt[u]];
        }
    };
    for(int i=0;i<2*n;i++){
        dfs(i);
    }
    int q;
    cin >> q;
    vector<pair<ll,int>> b;
    for(int i=0;i<q;i++){
        ll x;
        cin >> x;
        b.emplace_back(x,i);
    }
    sort(b.rbegin(),b.rend());
    vector<bool> ans(q);
    int idx=n-1;
    map<ll,int> mp;
    for(auto [x,i]:b){
        while(idx>=0&&a[idx]>=x){
            mp[(a[idx]-d[idx]+k)%k]=idx;
            idx--;
        }
        if(!mp.count(x%k)||dp[mp[x%k]*2]){
            ans[i]=true;
        }
    }
    for(auto x:ans){
        cout << (x?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}