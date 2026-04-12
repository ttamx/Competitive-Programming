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
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    if(n<3){
        sort(a.rbegin(),a.rend());
        cout << accumulate(a.begin(),a.begin()+k,0LL) << "\n";
        return;
    }
    k--;
    ll sum=0;
    multiset<ll> msl;
    multiset<ll,greater<ll>> msr;
    auto rebalance=[&](){
        while(msl.size()<k&&!msr.empty()){
            sum+=*msr.begin();
            msl.emplace(*msr.begin());
            msr.erase(msr.begin());
        }
        while(msl.size()>k){
            sum-=*msl.begin();
            msr.emplace(*msl.begin());
            msl.erase(msl.begin());
        }
    };
    auto insert=[&](ll x){
        sum+=x;
        msl.emplace(x);
        rebalance();
    };
    auto erase=[&](ll x){
        auto it=msr.find(x);
        if(it!=msr.end()){
            msr.erase(it);
        }else{
            sum-=x;
            msl.erase(msl.find(x));
            rebalance();
        }
    };
    int root=-1;
    for(int i=0;i<n;i++){
        if(adj[i].size()>1){
            root=i;
            break;
        }
    }
    assert(root!=-1);
    vector<pair<int,int>> mn(n),mn2(n);
    ll ans=0;
    vector<ll> b(n);
    function<void(int,int)> dfs=[&](int u,int p){
        mn[u]={0,u};
        mn2[u]={INF,-1};
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            mn2[u]=min(mn2[u],{mn[v].first-1,mn[v].second});
            if(mn2[u]<mn[u])swap(mn[u],mn2[u]);
        }
    };
    function<void(int,int,pair<int,int>)> dfs2=[&](int u,int p,pair<int,int> up){
        int x=mn[u].second;
        erase(b[x]);
        b[x]-=a[u];
        insert(b[x]);
        ans=max(ans,sum+a[u]);
        auto cur=mn[u];
        for(auto v:adj[u])if(v!=p){
            auto tmp=mn[v];
            tmp.first--;
            auto opt=min(up,tmp==mn[u]?mn2[u]:mn[u]);
            int w=opt.second;
            erase(b[w]);
            b[w]+=a[u];
            insert(b[w]);
            opt.first--;
            dfs2(v,u,opt);
            erase(b[w]);
            b[w]-=a[u];
            insert(b[w]);
        }
        erase(b[x]);
        b[x]+=a[u];
        insert(b[x]);
    };
    dfs(root,-1);
    for(int i=0;i<n;i++){
        b[mn[i].second]+=a[i];
    }
    for(auto x:b){
        insert(x);
    }
    dfs2(root,-1,{INF,-1});
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}