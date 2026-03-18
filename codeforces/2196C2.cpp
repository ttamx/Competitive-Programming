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
    cin >> n;
    auto ask=[&](int k){
        cout << "? " << k << endl;
        int s;
        cin >> s;
        vector<int> a(s);
        for(auto &x:a)cin >> x;
        return a;
    };
    vector<pair<int,int>> ans;
    vector<int> cnt(n+1,1);
    vector<bool> vis(n+1);
    int cur=1;
    vector<int> path;
    for(int i=1;i<=n;i++){
        cur+=cnt[i];
        if(vis[i])continue;
        vis[i]=true;
        vector<int> cpath{i};
        while(true){
            auto path=ask(cur);
            if(path.size()<2)break;
            assert(path[0]==i);
            int u=path.back();
            while(cpath.size()>=path.size())cpath.pop_back();
            ans.emplace_back(cpath.back(),u);
            for(auto x:cpath)cnt[x]+=cnt[u];
            cpath.emplace_back(u);
            cur+=cnt[u];
            vis[u]=true;
        }
    }
    cout << "! " << ans.size() << endl;
    for(auto [u,v]:ans)cout << u << " " << v << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}